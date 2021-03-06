/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:41 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/27 15:02:20 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_prompt() {
    char buf[512];
    const int size = 512;
    char *prompt = "(minishell)";
    prompt = ft_strjoin(prompt, getcwd(buf, size));
    prompt = ft_strjoin_with_free(prompt, true, "> ", false);
    return prompt;
}

int main(int argc, char **argv, char **envp) {
    t_minishell *ms = init_minishell(envp);
    int sts;
    
    using_history();
    // read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
    while (1) {
        char *prompt = get_prompt();
        char *str = readline(prompt);
        free(prompt);
        add_history(str);

        // check
        pid_t pid = fork();
        if (pid == 0) {
            t_token *tok = lexer(str);
            t_node *node = parser(tok);
            exit(0);
        }
        wait(&sts);
        if (sts != 0)
            continue;

        // lexer
        t_token *tok = lexer(str);
        if (DEBUG)
            debug_lexer(tok);
        
        // parser
        t_node *node = parser(tok);
        if (DEBUG)
            debug_parser(node);
        free_token(tok);

        // expander
        expander(ms, node);
        if (DEBUG)
            debug_expander(node);

        // exec
        if (DEBUG)
	        printf("exec::::::::::::::\n");
        exec(ms, node);

        free_node(node);
    }
    // write_history(".my_history");
}
