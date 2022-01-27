/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 01:44:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/27 14:10:48 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_export(t_env *env) {
    if (env->body == NULL) 
        printf("declare -x %s", env->name);
    else
        printf("declare -x %s=\"%s\"", env->name, env->body);
    printf("\n");
}

void export(t_minishell *ms, t_node *node) {
    node = node->cmds->next;
    if (node == NULL) {
        sort_env(ms);
        t_env *env = ms->envs;
        while (env) {
            print_export(env);
            env = env->next;
        }
        return;
    }

    while (node) {
        char *plus_eq = ft_strnstr(node->str, "+=", ft_strlen(node->str));
        char *eq = ft_strchr(node->str, '=');
        if (plus_eq && plus_eq < eq) {
            char *name = ft_strndup(node->str, plus_eq - node->str);
            char *body = ft_strdup(plus_eq + 2);
            t_env *env = find_env(ms, name);
            if (env) {
                env->body = ft_strjoin_with_free(env->body, true, body, false);
            } else {
                char *new_env = ft_strjoin_with_free(name, false, "=", false);
                new_env = ft_strjoin_with_free(new_env, true, body, false);
                add_env(ms, new_env);
            }
            free(name);
            free(body);
        }
        else {
            add_env(ms, node->str);
        }
        node = node->next;
    }
}
