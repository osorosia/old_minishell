/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 01:36:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/22 01:39:57 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo(t_minishell *ms, t_node *node) {
    node = node->cmds->next;
    while (node != NULL) {
        printf("%s", node->str);
        node = node->next;
        if (node != NULL)
            printf(" ");
    }
    printf("\n");
}
