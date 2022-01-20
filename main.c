/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:41 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 10:25:30 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp) {
    char *prompt = "minishell>";

    t_minishell *ms = init_minishell(envp);
    
    using_history();
    read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
    while (1) {
        char *str = readline(prompt);

        // lexer
        t_token *tok = lexer(str);
        debug_lexer(tok);
        
        // parser
        t_node *node = parser(tok);
        debug_parser(node);
        free_lexer(tok);

        // expander
        expander(ms, node);
        debug_expander(node);

        free_parser(node);
        add_history(str);
    }
    write_history(".my_history");
}

// build:
//   gcc read.c -L/usr/include -lreadline
