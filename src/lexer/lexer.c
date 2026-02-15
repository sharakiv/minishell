/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 18:17:44 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/07 07:27:46 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	handle_lexer_error(t_token **tokens);
static void	process_char(t_lexer_context *ctx, t_token **tokens);
static void	lexer_normal_state(t_lexer_context *ctx, t_token **tokens);
static int	finalize_tokens(t_lexer_context *ctx, t_token **tokens);

void	lexer(char *input, t_token **tokens)
{
	t_lexer_context	ctx;

	*tokens = NULL;
	init_lexer_context(&ctx, input);
	while (*ctx.input != '\0')
	{
		process_char(&ctx, tokens);
		if (ctx.error_shown)
			return ;
		ctx.input++;
	}
	if (has_unclosed_quotes(&ctx))
	{
		print_quotes_error(&ctx);
		handle_lexer_error(tokens);
		return ;
	}
	finalize_tokens(&ctx, tokens);
}

static int	handle_lexer_error(t_token **tokens)
{
	if (*tokens)
		free_token_list(*tokens);
	*tokens = NULL;
	return (0);
}

static int	finalize_tokens(t_lexer_context *ctx, t_token **tokens)
{
	t_token	*eof_token;

	if (!flush_word_buffer(ctx, tokens))
		return (handle_lexer_error(tokens));
	if (*tokens == NULL)
		return (1);
	eof_token = create_token(TOKEN_EOF, "");
	if (!eof_token)
		return (handle_lexer_error(tokens));
	add_token_to_list(tokens, eof_token);
	return (1);
}

static void	process_char(t_lexer_context *ctx, t_token **tokens)
{
	char	current_char;

	current_char = *ctx->input;
	if (ctx->state == STATE_IN_QUOTE)
	{
		check_single_quote_state(ctx, current_char);
	}
	else if (ctx->state == STATE_IN_DQUOTE)
	{
		check_double_quote_state(ctx, current_char);
	}
	else
	{
		lexer_normal_state(ctx, tokens);
	}
}

static void	lexer_normal_state(t_lexer_context *ctx, t_token **tokens)
{
	char	current_char;

	current_char = *ctx->input;
	if (current_char == '\'')
		ctx->state = STATE_IN_QUOTE;
	else if (current_char == '"')
		ctx->state = STATE_IN_DQUOTE;
	else if (is_ifs_char(current_char))
		flush_word_buffer(ctx, tokens);
	else if (current_char == '|')
		tokenize_pipe(ctx, tokens);
	else if (current_char == '>')
		tokenize_redirect_out(ctx, tokens);
	else if (current_char == '<')
		tokenize_redirect_in(ctx, tokens);
	else
		add_char_to_buffer(ctx, current_char);
}
