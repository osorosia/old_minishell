/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:38 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 08:41:45 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node *new_node_pipe(t_node *lhs, t_node *rhs) {
    t_node *node = ft_calloc(1, sizeof(t_node));
    node->kind = ND_PIPE;
    node->lhs = lhs;
    node->rhs = rhs;
    return (node);
}

t_node *new_node_command() {
    t_node *node = ft_calloc(1, sizeof(t_node));
    node->kind = ND_CMD;
    return node;    
}

void add_command(t_node *cmd, t_node *word) {
    if (cmd->cmds == NULL) {
        cmd->cmds = word;
        return ;
    }
    t_node *last = cmd->cmds;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = word;
}

void add_command_redir_in(t_node *cmd, t_node *redir_in) {
    if (cmd->redir_in == NULL) {
        cmd->redir_in = redir_in;
        return ;
    }
    t_node *last = cmd->redir_in;
    while (last->next != NULL)
        last = last->next;
    last->next = redir_in;
}

void add_command_redir_out(t_node *cmd, t_node *redir_out) {
    if (cmd->redir_out == NULL) {
        cmd->redir_out = redir_out;
        return ;
    }
    t_node *last = cmd->redir_out;
    while (last->next != NULL)
        last = last->next;
    last->next = redir_out;
}

t_node *new_node_word(t_token *tok) {
    t_node *node = ft_calloc(1, sizeof(t_node));
    node->kind = ND_WORD;
    node->str = ft_strndup(tok->str, tok->len);
    return node;
}

t_node *parser(t_token *tok);
t_node *pipe_cmd(t_token **tok);
t_node *command(t_token **tok);
t_node *redir_in(t_token **tok);
t_node *redir_out(t_token **tok);
t_node *word(t_token **tok);

// parser = pipe_cmd EOF
t_node *parser(t_token *tok) {
    t_node *node = pipe_cmd(&tok);
    if (!equal(tok, TK_EOF, ""))
        error("parser error: expected EOF\n");
    return (node);
}

// pipe_cmd = command ("|" command)*
t_node *pipe_cmd(t_token **tok) {
    t_node *node = new_node_pipe(NULL, command(tok));

    while (equal(*tok, TK_OP, "|")) {
        *tok = skip(*tok, TK_OP, "|");
        node = new_node_pipe(node, command(tok));
    }
    return (node);
}

// command = word (word | redir_in | redir_out)*
t_node *command(t_token **tok) {
    t_node *node = new_node_command();
    add_command(node, word(tok));
    while (true) {
        if (equal(*tok, TK_WORD, NULL))
            add_command(node, word(tok));
        else if (equal(*tok, TK_OP, "<") || equal(*tok, TK_OP, "<<"))
            add_command_redir_in(node, redir_in(tok));
        else if (equal(*tok, TK_OP, ">") || equal(*tok, TK_OP, ">>"))
            add_command_redir_out(node, redir_out(tok));
        else
            break;
    }
    return node;
}

// redir_in = ("<" | "<<") word
t_node *redir_in(t_token **tok) {
    if (equal(*tok, TK_OP, "<"))
        skip(*tok, TK_OP, "<");
    else if (equal(*tok, TK_OP, "<<"))
        skip(*tok, TK_OP, "<<");
    t_node *node = word(tok);
    return node;
}

// redir_out = (">" | ">>") word
t_node *redir_out(t_token **tok) {
    if (equal(*tok, TK_OP, ">"))
        *tok = skip(*tok, TK_OP, ">");
    else if (equal(*tok, TK_OP, ">>"))
        *tok = skip(*tok, TK_OP, ">>");
    t_node *node = word(tok);
    return node;
}

// word = (e.g.) "ls", "-l", "file", ...
t_node *word(t_token **tok) {
    t_node *node;
    if (equal(*tok, TK_WORD, NULL))
        node = new_node_word(*tok);
    *tok = skip(*tok, TK_WORD, NULL);
    return node;
}

void free_parser(t_node *node) {
    if (node == NULL)
        return;
    free_parser(node->lhs);
    free_parser(node->rhs);
    free_parser(node->next);
    free_parser(node->cmds);
    free_parser(node->redir_in);
    free_parser(node->redir_out);
    free(node);
}
