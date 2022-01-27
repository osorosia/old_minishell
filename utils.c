/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:16:30 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/26 15:09:11 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void error(char *str)
{
    ft_putstr_fd(str, 2);
    exit(1);
}

void debug(char *format, ...)
{
    va_list ap;
    va_start(ap, format);
    vfprintf(stderr, format, ap);
    va_end(ap);
}

char	*ft_strjoin_with_free(char *s1, bool f1, char *s2, bool f2) {
    char *str = ft_strjoin(s1, s2);
    if (f1)
        free(s1);
    if (f2)
        free(s2);
    return str;
}

bool check_x(char *path) {
    return (access(path, X_OK) == 0);
}

int ft_strcmp(char *s1, char *s2) {
    unsigned char *p1 = s1;
    unsigned char *p2 = s2;

    int i = 0;
    while (p1[i] == p2[i] && p1[i] != '\0')
        i++;
    return ((int)p1[i] - p2[i]);
}
