/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:27:22 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 13:19:30 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void debug_expander_recursive(t_node *node, long indent) {
    if (node == NULL)
        return;
    
    if (node->kind == ND_PIPE) {
        if (node->lhs != NULL) {
            debug_expander_recursive(node->lhs, indent);
            printf("%*s----PIPE----\n", indent * INDENT_WIDTH, "");
        }
        debug_expander_recursive(node->rhs, indent);
    }

    if (node->kind == ND_CMD) {
        printf("%*scmds   : ", indent * INDENT_WIDTH, "");
        t_node *cmd = node->cmds;
        while (cmd) {
            printf("'%s' ", cmd->str);
            cmd = cmd->next;
        }
        printf("\n");
        indent++;
        if (node->is_builtin)
            printf("%*s- builtin\n", indent * INDENT_WIDTH, "");
        if (node->pathname)
            printf("%*s- path: %s (%s)\n", indent * INDENT_WIDTH, "",
                    node->pathname,
                    node->is_exist ? "exist" : "not found");
        indent--;
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

void debug_expander(t_node *node) {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("expander::::::::::::::\n");
    debug_expander_recursive(node, 1);
}
