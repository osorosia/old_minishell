/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 01:44:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/22 01:55:56 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void export(t_minishell *ms, t_node *node) {
    node = node->cmds->next;
    if (node == NULL) {
        return;
    }

    while (node) {
        if (ft_strchr(node->str, '=')) {
            add_env(ms, node->str);
        }
        node = node->next;
    }
}
