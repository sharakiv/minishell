/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:32:06 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/07 17:18:55 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

void	check_single_quote_state(t_lexer_context *ctx, char current_char)
{
	if (current_char == '\'')
	{
		add_char_to_buffer(ctx, '\x02');
		ctx->state = STATE_NORMAL;
	}
	else if (current_char == '$')
	{
		add_char_to_buffer(ctx, '\x01');
		add_char_to_buffer(ctx, current_char);
	}
	else
		add_char_to_buffer(ctx, current_char);
}

void	check_double_quote_state(t_lexer_context *ctx, char current_char)
{
	if (current_char == '"')
	{
		add_char_to_buffer(ctx, '\x02');
		ctx->state = STATE_NORMAL;
	}
	else
		add_char_to_buffer(ctx, current_char);
}

int	has_unclosed_quotes(t_lexer_context *ctx)
{
	if (ctx->state == STATE_IN_QUOTE || ctx->state == STATE_IN_DQUOTE)
		return (1);
	return (0);
}

void	print_quotes_error(t_lexer_context *ctx)
{
	if (ctx->state == STATE_IN_QUOTE)
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed single quote\n",
			47);
		return ;
	}
	if (ctx->state == STATE_IN_DQUOTE)
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed double quote\n",
			47);
		return ;
	}
	return ;
}
