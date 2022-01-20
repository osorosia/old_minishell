/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:15:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 09:23:40 by rnishimo         ###   ########.fr       */
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

typedef enum e_node_kind t_node_kind;
enum e_node_kind {
	ND_CMD,
	ND_PIPE,
	ND_WORD,
};

typedef struct s_node t_node;
struct s_node {
	t_node_kind kind;
	t_node *next;

	// pipe
	t_node *lhs;
	t_node *rhs;

	// cmd
	t_node *cmds;      // linked-list
	t_node *redir_in;  // linked-list
	t_node *redir_out; // linked-list

	// word
	char *str;
};

typedef struct s_env t_env;
struct s_env {
	t_env	*next;	// linked list
	char	*name;	// e.g. PATH
	char	*body;	// e.g. /usr/bin:/bin
};

typedef struct s_minishell t_minishell;
struct s_minishell {
	t_env	*envs;	// environment variables
	long	env_size;

	long	status; // exit status
};

//
// lexer
//

// lexer.c
t_token *lexer(char *p);
void	free_lexer(t_token *tok);
t_token *skip(t_token *tok, t_token_kind kind, char *str);
bool	equal(t_token *tok, t_token_kind kind, char *str);

// debug_lexer.c
void debug_lexer(t_token *token);

//
// parser
//

// parser.c
t_node *parser(t_token *tok);
void free_parser(t_node *node);

// debug_parser.c
void debug_parser(t_node *node);

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

// ms.c
t_minishell *init_minishell(char *envp[]);
void 		free_minishell(t_minishell *ms);
void 		add_env(t_minishell *ms, char *str);
t_env   	*find_env(t_minishell *ms, char *name);

#endif
