/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 10:17:12 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 13:14:10 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_path(t_minishell *ms, t_node *node) {
    char *str = node->cmds->str;
    if (ft_strchr(str, '/')) {
        node->is_exist = check_x(str);
        node->pathname = ft_strdup(str);
        return ;
    }
    str = ft_strjoin("/", str);
    char **paths = get_paths(ms);
    
    int i = 0;
    while (paths[i]) {
        char *pathname = ft_strjoin(paths[i++], str);
        if (check_x(pathname)) {
            node->pathname = pathname;
            node->is_exist = true;
            break;
        }
        free(pathname);
    }
    free(paths);
}

void filename_generation(t_minishell *ms, t_node *node) {
    if (node == NULL)
        return;
    if (node->kind == ND_PIPE) {
        filename_generation(ms, node->lhs);
        filename_generation(ms, node->rhs);
    }
    if (node->kind == ND_CMD) {
        // cmds
        if (check_builtin(node->cmds->str))
            node->is_builtin = true;
        else
            check_path(ms, node);
        // redirect
    }
}

void expander(t_minishell *ms, t_node *node) {
    filename_generation(ms, node);
}
