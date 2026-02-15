/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:57:05 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:15:35 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static void	cleanup_tokens(t_lexer_context *ctx, t_token **tokens);

static int	validate_redirect(t_lexer_context *ctx, int offset)
{
	char	*pos;
	char	token_str[3];
	int		is_double;

	pos = ctx->input + offset;
	while (*pos == ' ' || *pos == '\t')
		pos++;
	if (*pos == '\0' || *pos == '\n')
		return (write_syntax_error("newline"), 0);
	if (*pos == '|' || *pos == '>' || *pos == '<')
	{
		is_double = ((*pos == '>' && *(pos + 1) == '>') || (*pos == '<' && *(pos
						+ 1) == '<'));
		token_str[0] = *pos;
		token_str[1] = '\0';
		if (is_double)
		{
			token_str[1] = *(pos + 1);
			token_str[2] = '\0';
		}
		return (write_syntax_error(token_str), 0);
	}
	return (1);
}

void	tokenize_redirect_in(t_lexer_context *ctx, t_token **tokens)
{
	t_token	*new_token;
	int		is_heredoc;

	flush_word_buffer(ctx, tokens);
	is_heredoc = (ctx->input[0] == '<' && ctx->input[1] == '<');
	if (!validate_redirect(ctx, is_heredoc + 1))
	{
		if (is_heredoc)
			ctx->input++;
		return (cleanup_tokens(ctx, tokens));
	}
	if (is_heredoc)
	{
		new_token = create_token(TOKEN_HEREDOC, "<<");
		ctx->input++;
	}
	else
		new_token = create_token(TOKEN_REDIRECT_IN, "<");
	if (!new_token)
		return (cleanup_tokens(ctx, tokens));
	add_token_to_list(tokens, new_token);
}

void	tokenize_redirect_out(t_lexer_context *ctx, t_token **tokens)
{
	t_token	*new_token;
	int		is_append;

	flush_word_buffer(ctx, tokens);
	is_append = (ctx->input[0] == '>' && ctx->input[1] == '>');
	if (!validate_redirect(ctx, is_append + 1))
	{
		if (is_append)
			ctx->input++;
		return (cleanup_tokens(ctx, tokens));
	}
	if (is_append)
	{
		new_token = create_token(TOKEN_REDIRECT_APPEND, ">>");
		ctx->input++;
	}
	else
		new_token = create_token(TOKEN_REDIRECT_OUT, ">");
	if (!new_token)
		return (cleanup_tokens(ctx, tokens));
	add_token_to_list(tokens, new_token);
}

static void	cleanup_tokens(t_lexer_context *ctx, t_token **tokens)
{
	free_token_list(*tokens);
	*tokens = NULL;
	ctx->error_shown = 1;
}
