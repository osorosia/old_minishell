/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:23:38 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/21 00:58:52 by rnishimo         ###   ########.fr       */
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

void exec_recursive(t_minishell *ms, t_node *node) {
    int fd[2];
    pid_t pid;
    int sts;

    if (node == NULL)
        return ;
    if (node->kind == ND_PIPE) {
        exec_recursive(ms, node->lhs);
        exec_recursive(ms, node->rhs);
    }
    if (node->kind == ND_CMD) {
        if (node->is_builtin) {
            builtin(ms, node);
        }
        else if (node->is_exist) {
            exec_file(node->pathname, create_cmds(node->cmds), create_envp(ms->envs));
        }
        else
            fprintf(stderr, "minishell: %s: command not found\n", node->cmds->str);
    }
}

void exec(t_minishell *ms, t_node *node) {
    exec_recursive(ms, node);
}
