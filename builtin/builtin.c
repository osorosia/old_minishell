/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:55:43 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/21 01:00:31 by rnishimo         ###   ########.fr       */
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

void builtin(t_minishell *ms, t_node *node) {
    // char **strs = 
    if (!strncmp(node->cmds->str, "echo", ft_strlen("echo") + 1))
        printf("echo\n");
    else if (!strncmp(node->cmds->str, "cd", ft_strlen("cd") + 1))
        printf("cd\n");
    else if (!strncmp(node->cmds->str, "pwd", ft_strlen("pwd") + 1))
        printf("pwd\n");
    else if (!strncmp(node->cmds->str, "export", ft_strlen("export") + 1))
        printf("export\n");
    else if (!strncmp(node->cmds->str, "unset", ft_strlen("unset") + 1))
        printf("unset\n");
    else if (!strncmp(node->cmds->str, "env", ft_strlen("env") + 1))
        printf("env\n");
    else if (!strncmp(node->cmds->str, "exit", ft_strlen("exit") + 1))
        printf("exit\n");
    else
        error("unexpected builtin\n");
}
