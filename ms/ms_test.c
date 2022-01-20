/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 14:19:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 12:15:59 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <assert.h>
#include <string.h>

void test() {
    char *input = "TEST=aaaaa";
    char *expected = "aaaaa";
    printf("%s => ", input);

    t_minishell *ms = init_minishell(NULL);
    add_env(ms, input);    
    assert(strcmp(find_env(ms, "TEST")->body, "aaaaa") == 0);
    free_minishell(ms);

    // result
    printf("%s\n", expected);
}

void test_get_paths(char **envp) {
    printf("PATH => ");

    t_minishell *ms = init_minishell(envp);

    char **paths = get_paths(ms);
    assert(paths != NULL);

    for (int i = 0; paths[i]; i++)
        printf("'%s' ", paths[i]);
    printf("\n");

    free_minishell(ms);
}

int main(int argc, char **argv, char **envp) {
    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("ms =================================\n");
    // add_env(), find_env()
    test();
    // get_paths()
    test_get_paths(envp);
    printf("ms OK ==============================\n");
}
