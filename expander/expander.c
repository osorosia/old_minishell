/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:17:12 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 11:00:21 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void filename_generation(t_minishell *ms, t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_PIPE) {
        filename_generation(ms, node->lhs);
        filename_generation(ms, node->rhs);
    }
    if (node->kind == ND_CMD) {
        
    }
}

void expander(t_minishell *ms, t_node *node) {
    filename_generation(ms, node);
}
