/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/19 11:56:18 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

// status
#define EXIT_CMD_NOT_FOUND 127

typedef enum e_token_kind {
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

typedef struct s_env t_env;
struct s_env {
	t_env	*next;	// linked list
	char	*name;	// e.g. PATH
	char	*str;	// e.g. /usr/bin:/bin
};

typedef struct s_minishell t_minishell;
struct s_minishell {
	t_env	*envs;	// environment variables
	long	status; // exit status
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
// exec
//

// exec.c
int exec(char *cmds[], char *envp[]);

//
// minishell
//

// utils.c
void error(char *str);
void debug(char *format, ...);

#endif
