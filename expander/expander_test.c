/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:24 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/17 06:21:22 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <assert.h>

void test() {
    t_token *tok = lexer("aaa");
    free_lexer(tok);
}

int main(int argc, char **argv) {
    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    test();

    printf("expander: OK\n");
}
