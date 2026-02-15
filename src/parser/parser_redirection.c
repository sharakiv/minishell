/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:56:00 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/10 22:50:51 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	check_redirect_has_target(t_token *tok)
{
	if (!tok->next || tok->next->type == TOKEN_EOF)
	{
		write_syntax_error("newline");
		return (0);
	}
	return (1);
}

static int	check_redirect_target_valid(t_token *tok)
{
	if (is_operator_token(tok->next->type))
	{
		write_syntax_error(tok->next->content);
		return (0);
	}
	return (1);
}

int	check_redirect_syntax(t_token *tokens)
{
	t_token	*tok;

	tok = tokens;
	while (tok && tok->type != TOKEN_EOF)
	{
		if (is_redirect_token(tok->type))
		{
			if (!check_redirect_has_target(tok))
				return (0);
			if (!check_redirect_target_valid(tok))
				return (0);
		}
		tok = tok->next;
	}
	return (1);
}
