/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:23:38 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/17 07:11:57 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec(char *cmds[], char *envp[]) {
    int sts; // command not found
    pid_t pid = fork();
    if (pid == 0) {
        execve(cmds[0], cmds, envp);
        exit(EXIT_CMD_NOT_FOUND);
    }
    waitpid(pid, &sts, 0);
    return WEXITSTATUS(sts);
}
