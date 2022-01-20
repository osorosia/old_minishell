/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 08:31:58 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 10:13:43 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define INDENT_WIDTH 4

void debug_parser_recursive(t_node *node, long indent) {
    if (node == NULL)
        return;
    
    if (node->kind == ND_PIPE) {
        if (node->lhs != NULL) {
            debug_parser_recursive(node->lhs, indent);
            printf("%*s----PIPE----\n", indent * INDENT_WIDTH, "");
        }
        debug_parser_recursive(node->rhs, indent);
    }

    if (node->kind == ND_CMD) {
        printf("%*scmds   : ", indent * INDENT_WIDTH, "");
        t_node *cmd = node->cmds;
        while (cmd) {
            printf("'%s' ", cmd->str);
            cmd = cmd->next;
        }
        printf("\n");

        if (node->redir_in) {
            printf("%*sred_in : ", indent * INDENT_WIDTH, "");
            t_node *redir_in = node->redir_in;
            while (redir_in) {
                printf("'%s' ", redir_in->str);
                redir_in = redir_in->next;
            }
            printf("\n");
        }

        if (node->redir_out) {
            printf("%*sred_out: ", indent * INDENT_WIDTH, "");
            t_node *redir_out = node->redir_out;
            while (redir_out) {
                printf("'%s' ", redir_out->str);
                redir_out = redir_out->next;
            }
            printf("\n");
        }
    }
}

void debug_parser(t_node *node) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("parser::::::::::::::\n");
    debug_parser_recursive(node, 1);
}
