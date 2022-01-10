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


// tokenize.c
t_token *tokenize(char *p);
void debug_tokenize(t_token *token);

// utils.c
void error(char *str);
