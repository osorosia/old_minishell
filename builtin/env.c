/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 01:26:48 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/22 02:18:47 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env(t_env *env) {
    printf("%s=%s\n", env->name, env->body);
}

void env(t_minishell *ms, t_node *node) {
    t_env *env = ms->envs;
    while (env) {
        print_env(env);
        env = env->next;
    }
}
