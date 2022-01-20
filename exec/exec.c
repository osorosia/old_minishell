/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:23:38 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 13:44:29 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_file(char *pathname, char *cmds[], char *envp[]) {
    int sts; // command not found
    pid_t pid = fork();
    if (pid == 0) {
        execve(pathname, cmds, envp);
        exit(EXIT_CMD_NOT_FOUND);
    }
    waitpid(pid, &sts, 0);
    return WEXITSTATUS(sts);
}
