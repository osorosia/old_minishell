/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:03:29 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/19 12:42:41 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *init_minishell(char *envp[]) {
    t_minishell *ms = malloc(sizeof(t_minishell));
    
    ms->status = 0;
    int i = 0;
    while (envp[i])
        add_env(ms, envp[i++]);
    return (ms);
}

void free_minishell(t_minishell *ms) {
    t_env *next;

    while (ms->envs) {
        next = ms->envs->next;
        free(ms->envs);
        ms->envs = next;
    }
    free(ms);
}

void add_env(t_minishell *ms, char *str) {
    t_env *env;

    char *name = ft_substr(str, 0, ft_strchr(str, '='));
    char *body = ft_substr(str, ft_strchr(str, '=') + 1, ft_strchr(str, '\0'));

    env = find_env(ms, name);
    if (env) {
        free(name);
        free(env->body);
        env->body = body;
        return;
    }
    
    t_env *env = malloc(sizeof(t_env));
    env->name = name;
    env->body = body;
    env->next = ms->envs;
    ms->envs = env;
}

t_env   *find_env(t_minishell *ms, char *name) {
    t_env *env = ms->envs;

    while (env) {
        if (ft_strncmp(env->name, name, ft_strlen(name) + 1) == 0)
            return (env);
        env = env->next;
    }
    return (NULL);
}
