/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:56:47 by sharaki           #+#    #+#             */
/*   Updated: 2025/11/11 20:56:50 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_redirect_list(t_redirect *redirects)
{
	t_redirect	*tmp;

	while (redirects)
	{
		tmp = redirects;
		redirects = redirects->next;
		free(tmp->file);
		free(tmp);
	}
}

void	free_heredoc_list(t_heredoc *heredocs)
{
	t_heredoc	*tmp;

	while (heredocs)
	{
		tmp = heredocs;
		heredocs = heredocs->next;
		free(tmp->delimiter);
		free(tmp->content);
		free(tmp);
	}
}

t_cmd	*cleanup_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return (NULL);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->quote_types)
		free(cmd->quote_types);
	if (cmd->redirects)
		free_redirect_list(cmd->redirects);
	if (cmd->heredocs)
		free_heredoc_list(cmd->heredocs);
	free(cmd);
	return (NULL);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		cleanup_cmd(tmp);
	}
}
