/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:03:29 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/24 05:26:51 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell *init_minishell(char *envp[]) {
    t_minishell *ms = ft_calloc(1, sizeof(t_minishell));
    
    int i = 0;
    while (envp && envp[i])
        add_env(ms, envp[i++]);
    return (ms);
}

void free_env(t_env *env) {
    free(env->name);
    free(env->body);
    free(env);
}

void free_minishell(t_minishell *ms) {
    t_env *next;

    while (ms->envs) {
        next = ms->envs->next;
        free_env(ms->envs);
        ms->envs = next;
    }
    free(ms);
}

void add_env(t_minishell *ms, char *str) {
    t_env *env;

    char *name = ft_substr(str, 0, ft_strlen_to_c(str, '='));
    char *body = ft_substr(ft_strchr(str, '=') + 1, 0, ft_strlen(ft_strchr(str, '=') + 1));

    env = find_env(ms, name);
    if (env) {
        free(name);
        free(env->body);
        env->body = body;
        return;
    }
    
    env = ft_calloc(1, sizeof(t_env));
    env->name = name;
    env->body = body;
    env->next = ms->envs;
    env->prev = NULL;
    if (ms->envs)
        ms->envs->prev = env;
    ms->envs = env;
    ms->env_size++;
}

void rm_env(t_minishell *ms, char *name) {
    t_env *env = find_env(ms, name);
    if (env == NULL)
        return ;
    
    t_env *prev = env->prev;
    t_env *next = env->next;
    if (!prev)
        ms->envs = next;
    if (prev)
        prev->next = next;
    if (next)
        next->prev = prev;
    free_env(env);
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

char **get_paths(t_minishell *ms) {
    t_env *env = find_env(ms, "PATH");
    if (env == NULL)
        return NULL;
    return (ft_split(env->body, ':'));
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
