/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:41 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/21 00:34:34 by rnishimo         ###   ########.fr       */
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
    
    using_history();
    read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
    while (1) {
        char *prompt = get_prompt();
        char *str = readline(prompt);
        free(prompt);

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
        add_history(str);
    }
    write_history(".my_history");
}
