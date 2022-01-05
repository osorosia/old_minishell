#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"

void call(char *pathname, char **argv) {
    // printf("pathname:%s\n", pathname);
    pid_t pid = fork();
    if (pid == 0)
        execve(pathname, argv, NULL);
    int sts;
    waitpid(pid, &sts, 0);
}

void exec(char *envp[], char *command) {

    char **commands = ft_split(command, ' ');

    char *str = commands[0];
    while (*envp)
    {
        if (ft_strnstr(*envp, "PATH", 4))
        {
            str = ft_strdup(*envp);
            break;
        }
        envp++;
    }
    str = ft_strchr(str, '=');
    str++;
    char **ls = ft_split(str, ':');

    command = ft_strjoin("/", commands[0]);
    while (*ls) {
        // printf("%s\n", ft_strjoin(*ls, command)c);
        int ok = access(ft_strjoin(*ls, command), X_OK);
        if (ok == F_OK)
            call(ft_strjoin(*ls, command), commands);
        ls++;
    }
    if (*ls) {
        printf("ng\n");
    }
}

int main(int argc, char **argv, char *envp[]) {
    char buf[4096];

    while (1) {
        write(1, "minishell> ", 11);
        int byte = read(0, buf, 4096);

        exec(envp, ft_substr(buf, 0, byte - 1));
    }
}
