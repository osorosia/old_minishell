/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 01:36:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/25 09:47:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void echo(t_minishell *ms, t_node *node) {
    bool n_op = false;
    node = node->cmds->next;

    if (node->str[0] == '-' && node->str[1] == 'n') {
        long i = 2;
        while (node->str[i] == 'n')
            i++;
        if (node->str[i] == '\0') {
            n_op = true;
            node = node->next;
        }
    }

    while (node != NULL) {
        printf("%s", node->str);
        node = node->next;
        if (node != NULL)
            printf(" ");
    }
    if (!n_op)
        printf("\n");
}
