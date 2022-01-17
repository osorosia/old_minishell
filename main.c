/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:41 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/17 06:15:41 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main() {
    char *prompt = "minishell>";
    
    using_history();
    read_history(".my_history"); // [ToDo]historyファイルが無いときの動作の検証
    while (1) {
        char *str = readline(prompt);

        // lexer
        t_token *tok = lexer(str);
        debug_lexer(tok);
        
        add_history(str);
    }
    write_history(".my_history");
}

// build:
//   gcc read.c -L/usr/include -lreadline
