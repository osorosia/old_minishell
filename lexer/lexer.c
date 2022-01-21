/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:16:09 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/21 00:34:34 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(t_token_kind kind, char *p, size_t len)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		error("malloc error\n");
	token->kind = kind;
	token->str = p;
	token->len = len;
	return (token);
}

size_t get_operator_len(char *p)
{
	const char *kw[] = {"<<", ">>", "<", ">", "|", "'", "\"", NULL};
	size_t  i;

	i = 0;
	while (kw[i] != NULL)
	{
		if (!ft_strncmp(kw[i], p, ft_strlen(kw[i])))
			return (ft_strlen(kw[i]));
		i++;
	}
	return (0);
}

size_t  get_word_len(char *p)
{
	size_t  len;

	len = 0;
	while (!ft_strchr(" ><|'\"", p[len]))
		len++;
	return (len);
}

t_token *lexer(char *p)
{
	t_token	*cur;
	t_token	head;

	head.next = NULL;
	cur = &head;
	while (*p)
	{
		while (*p == ' ')
			p++;

		if (get_operator_len(p))
		{
			cur = cur->next = new_token(TK_OP, p, get_operator_len(p));
			p += cur->len;
			continue;
		}

		if (get_word_len(p))
		{
			cur = cur->next = new_token(TK_WORD, p, get_word_len(p));
			p += cur->len;
			continue;
		}
		error("invalid character\n");
	}
	cur->next = new_token(TK_EOF, p, 0);
	return (head.next);
}

void free_token(t_token *tok) {
	t_token	*next;

	while (tok->kind != TK_EOF) {
		next = tok->next;
		free(tok);
		tok = next;
	}
	free(tok);
}

t_token *skip(t_token *tok, t_token_kind kind, char *str) {
	if (tok->kind != kind)
		error("skip error : unexpected kind\n");
	if (str != NULL && ft_strncmp(tok->str, str, tok->len))
		error("skip error : unexpectrd str\n");
	return tok->next;
}

bool equal(t_token *tok, t_token_kind kind, char *str) {
	if (tok->kind != kind)
		return false;
	if (str != NULL && ft_strncmp(tok->str, str, tok->len))
		return false;
	return true;
}
