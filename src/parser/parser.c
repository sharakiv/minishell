/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:55:12 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/03 17:48:52 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int			validate_syntax(t_token *tokens);
static int	parse_and_add_command(t_cmd **cmd_list, t_token *start,
				t_token *end);

t_cmd	*parse_pipeline(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_token	*cmd_start;
	t_token	*cmd_end;

	if (!validate_syntax(tokens))
		return (NULL);
	cmd_list = NULL;
	cmd_start = tokens;
	while (cmd_start && cmd_start->type != TOKEN_EOF)
	{
		cmd_end = find_command_end(cmd_start);
		if (!parse_and_add_command(&cmd_list, cmd_start, cmd_end))
			return (free_cmd_list(cmd_list), NULL);
		cmd_start = get_next_command_start(cmd_end);
	}
	return (cmd_list);
}

static int	parse_and_add_command(t_cmd **cmd_list, t_token *start,
		t_token *end)
{
	t_cmd	*new_cmd;
	t_cmd	*last;

	new_cmd = parse_single_command(start, end);
	if (!new_cmd)
		return (0);
	if (!*cmd_list)
	{
		*cmd_list = new_cmd;
		return (1);
	}
	last = *cmd_list;
	while (last->next)
		last = last->next;
	last->next = new_cmd;
	return (1);
}

int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (0);
	if (!check_pipe_syntax(tokens))
		return (0);
	if (!check_redirect_syntax(tokens))
		return (0);
	return (1);
}
