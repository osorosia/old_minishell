/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:23:38 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 23:14:05 by rnishimo         ###   ########.fr       */
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

char **create_cmds(t_node *cmds) {
    long size = 0;
    t_node *tmp = cmds;
    while (tmp) {
        size++;
        tmp = tmp->next;
    }

    char **strs = (char **)ft_calloc(size + 1, sizeof(char *));
    int i = 0;
    while (cmds) {
        strs[i++] = cmds->str;
        cmds = cmds->next;
    }
    return strs;
}

char **create_envp(t_env *env) {
    long size = 0;
    t_env *tmp = env;
    while (tmp) {
        size++;
        tmp = tmp->next;
    }

    char **strs = (char **)ft_calloc(size + 1, sizeof(char *));
    int i = 0;
    while (env) {
        strs[i] = ft_strjoin(env->name, "=");
        strs[i] = ft_strjoin_with_free(strs[i], true, env->body, false);
        i++;
        env = env->next;
    }
    return strs;
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
            // TODO
        }
        else if (node->is_exist) {
            pid = fork;
            if (pid == 0) {
                exec_file(node->pathname, create_cmds(node->cmds), create_envp(ms->envs));
                return 127;
            }
            wait(&sts);
        }
        else
            fprintf(stderr, "minishell: %s: command not found\n", node->cmds->str);
    }
}

void exec(t_minishell *ms, t_node *node) {
    exec_recursive(ms, node);
}
