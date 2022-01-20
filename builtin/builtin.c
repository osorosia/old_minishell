/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:55:43 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 11:33:30 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool check_builtin(char *str) {
    const char *cmds[] = {
        "echo",
        "cd",
        "pwd",
        "export",
        "unset",
        "env",
        "exit",
        NULL,
    };

    int i = 0;
    while (cmds[i]) {
        if (ft_strncmp(str, cmds[i], ft_strlen(cmds[i]) + 1) == 0) {
            return true;
        }
        i++;
    }
    return false;
}
