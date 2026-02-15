/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validation_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:34 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/10 22:49:39 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	check_pipe_at_start(t_token *tokens)
{
	if (tokens && tokens->type == TOKEN_PIPE)
	{
		write_syntax_error("|");
		return (0);
	}
	return (1);
}

static int	check_consecutive_pipes(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
	{
		if (tok->next && tok->next->type == TOKEN_PIPE)
		{
			write_syntax_error("|");
			return (0);
		}
	}
	return (1);
}

static int	check_pipe_at_end(t_token *tok)
{
	if (tok->type == TOKEN_PIPE)
	{
		if (!tok->next || tok->next->type == TOKEN_EOF)
		{
			write_syntax_error("newline");
			return (0);
		}
	}
	return (1);
}

int	check_pipe_syntax(t_token *tokens)
{
	t_token	*tok;

	if (!check_pipe_at_start(tokens))
		return (0);
	tok = tokens;
	while (tok && tok->type != TOKEN_EOF)
	{
		if (!check_consecutive_pipes(tok))
			return (0);
		if (!check_pipe_at_end(tok))
			return (0);
		tok = tok->next;
	}
	return (1);
}
