/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:07:20 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/17 06:07:56 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void debug_lexer(t_token *token)
{
	const char *kind[] = {
		"TK_OP",
		"TK_WORD",
		"TK_EOF"
	};

	while (token)
	{
		printf("{kind:%-7s, str:%.*s}\n", 
			kind[token->kind],
			token->len,
			token->str);
		token = token->next;
	}
}
