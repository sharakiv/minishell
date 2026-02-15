/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:30:28 by sharaki           #+#    #+#             */
/*   Updated: 2025/09/28 03:35:58 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	tokenize_pipe(t_lexer_context *ctx, t_token **tokens)
{
	t_token	*new_token;

	flush_word_buffer(ctx, tokens);
	new_token = create_token(TOKEN_PIPE, "|");
	if (!new_token)
	{
		free_token_list(*tokens);
		*tokens = NULL;
		return ;
	}
	add_token_to_list(tokens, new_token);
}
