/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 02:33:50 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/22 02:43:28 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void unset(t_minishell *ms, t_node *node) {
    node = node->cmds->next;
    while (node) {
        rm_env(ms, node->str);
        node = node->next;
    }
}
