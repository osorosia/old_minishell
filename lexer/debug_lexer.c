/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 06:07:20 by rnishimo          #+#    #+#             */
/*   Updated: 2022/01/20 09:09:03 by rnishimo         ###   ########.fr       */
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

	printf("lexer::::::::::::::\n");
	while (token)
	{
		printf("    {kind:%-7s, str:%.*s}\n", 
			kind[token->kind],
			token->len,
			token->str);
		token = token->next;
	}
}
