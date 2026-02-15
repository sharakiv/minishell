/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:50 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 15:56:25 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->quote_types = NULL;
	cmd->redirects = NULL;
	cmd->heredocs = NULL;
	cmd->heredoc_fd = -1;
	cmd->in_pipeline = 0;
	cmd->next = NULL;
	return (cmd);
}

t_token	*find_command_end(t_token *start)
{
	t_token	*tok;

	tok = start;
	while (tok && tok->type != TOKEN_PIPE && tok->type != TOKEN_EOF)
		tok = tok->next;
	return (tok);
}

t_token	*get_next_command_start(t_token *cmd_end)
{
	if (!cmd_end || cmd_end->type == TOKEN_EOF)
		return (NULL);
	return (cmd_end->next);
}

int	is_redirect_token(t_token_type type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND);
}

int	is_operator_token(t_token_type type)
{
	return (type == TOKEN_PIPE || is_redirect_token(type));
}
