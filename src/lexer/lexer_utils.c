/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:56:58 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/07 18:18:22 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

void	init_lexer_context(t_lexer_context *ctx, char *input)
{
	ctx->input = input;
	ctx->original_input = input;
	ctx->state = STATE_NORMAL;
	ctx->buffer_index = 0;
	ctx->word_buffer[0] = '\0';
	ctx->error_shown = 0;
	ctx->current_quote_type = QUOTE_NONE;
}

int	flush_word_buffer(t_lexer_context *ctx, t_token **tokens)
{
	t_token	*new_token;

	if (ctx->buffer_index > 0)
	{
		ctx->word_buffer[ctx->buffer_index] = '\0';
		new_token = create_token(WORD, ctx->word_buffer);
		if (!new_token)
			return (0);
		new_token->quote_type = ctx->current_quote_type;
		add_token_to_list(tokens, new_token);
		ctx->buffer_index = 0;
		ctx->word_buffer[0] = '\0';
		ctx->current_quote_type = QUOTE_NONE;
	}
	return (1);
}

void	add_char_to_buffer(t_lexer_context *ctx, char c)
{
	if (ctx->buffer_index >= MINISHELL_TOKEN_MAX - 1)
	{
		if (!ctx->error_shown)
		{
			write(STDERR_FILENO, "minishell: argument line too long\n", 35);
			ctx->error_shown = 1;
		}
		return ;
	}
	ctx->word_buffer[ctx->buffer_index++] = c;
}
