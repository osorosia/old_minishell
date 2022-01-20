/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:17:12 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 11:50:04 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_path() {
    
}

void filename_generation(t_minishell *ms, t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_PIPE) {
        filename_generation(ms, node->lhs);
        filename_generation(ms, node->rhs);
    }
    if (node->kind == ND_CMD) {
        // cmds
        if (check_builtin(node->cmds->str))
            node->is_builtin = true;
        else
            check_path(ms, node);
        // redirect
    }
}

void expander(t_minishell *ms, t_node *node) {
    filename_generation(ms, node);
}
