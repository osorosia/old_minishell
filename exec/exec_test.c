/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:24 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 13:44:57 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <assert.h>

void test_exec_no_cmds(const int expected) {
    char *cmds[] = {"no_commands", NULL};
    
    printf("stdout >>>>>>>>>\n");
    assert(exec_file(cmds[0], cmds, NULL) == expected);
    printf("<<<<<<<<<<<<<<<<\n");

    for (int i = 0; cmds[i]; i++)
        printf("%s ", cmds[i]);
    printf("=> ");
    printf("exit:%d", expected);
    printf("\n");
}

void test_exec_ls(const int expected) {
    char *cmds[] = {"/bin/ls", NULL};
    
    printf("stdout >>>>>>>>>\n");
    assert(exec_file(cmds[0], cmds, NULL) == expected);
    printf("<<<<<<<<<<<<<<<<\n");

    for (int i = 0; cmds[i]; i++)
        printf("%s ", cmds[i]);
    printf("=> ");

    printf("exit:%d", expected);
    printf("\n");
}

int main(int argc, char **argv) {
    // automatic test
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("exec=================================\n");
    // exec()
    test_exec_no_cmds(EXIT_CMD_NOT_FOUND); // no_commands
    test_exec_ls(EXIT_SUCCESS); // /bin/ls

    printf("exec OK==============================\n");
}
