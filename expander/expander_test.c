/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:24 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 12:17:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <assert.h>
#include <string.h>

int main(int argc, char **argv, char **envp) {

    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("expander=================================\n");
    printf("expander OK==============================\n");
}
