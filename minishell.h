/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/17 06:15:45 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_kind{
	TK_OP = 0,
	TK_WORD,
	TK_EOF,
} t_token_kind;

typedef struct s_token t_token;
struct s_token {
	t_token_kind	kind;
	t_token			*next;
	char			*str;
	size_t			len;
};

//
// lexer
//

// lexer.c
t_token *lexer(char *p);
void free_lexer(t_token *tok);

// debug_lexer.c
void debug_lexer(t_token *token);

//
// minishell
//

// utils.c
void error(char *str);
