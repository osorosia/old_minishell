/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:24 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/19 20:40:46 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <assert.h>
#include <string.h>

void test() {
    char *input = "TEST=aaaaa";
    char *expected = "aaaaa";

    t_minishell *ms = init_minishell(NULL);
    add_env(ms, input);    
    assert(strcmp(find_env(ms, "TEST")->body, "aaaaa") == 0);
    free_minishell(ms);

    printf("%s => %s\n", input, expected);
}

int main(int argc, char **argv, char **envp) {

    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("expander =================================\n");
    // add_env(), find_env()
    test();
    printf("expander OK ==============================\n");
}
