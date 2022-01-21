/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:16:20 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/21 15:51:59 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void cd(t_minishell *ms, t_node *node) {
    char buf[512];
    node = node->cmds->next;
    if (node->next != NULL) {
        fprintf(stderr, "bash: cd: too many argument\n");
        return ;
    }
    chdir(node->str);
}
