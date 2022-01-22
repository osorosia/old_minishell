/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 01:44:27 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/22 02:15:50 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_export(t_env *env) {
    printf("declare -x %s=\"%s\"", env->name, env->body);
    printf("\n");
}

void export(t_minishell *ms, t_node *node) {
    node = node->cmds->next;
    if (node == NULL) {
        t_env *env = ms->envs;
        while (env) {
            print_export(env);
            env = env->next;
        }
        return;
    }

    while (node) {
        if (ft_strchr(node->str, '=')) {
            add_env(ms, node->str);
        }
        node = node->next;
    }
}
