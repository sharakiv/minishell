/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:28:45 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:15:56 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static void	do_expand_args(t_cmd *cmd, char **envp, int exit_status);
static void	expand_args(t_cmd *cmd, char **envp, int exit_status);
static void	expand_redirects(t_cmd *cmd, char **envp, int exit_status);

void	expand_cmd_list(t_cmd *cmd, char **envp, int exit_status)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		expand_args(current, envp, exit_status);
		expand_redirects(current, envp, exit_status);
		current = current->next;
	}
}

static void	do_expand_args(t_cmd *cmd, char **envp, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args[i])
	{
		expanded = expand_string(cmd->args[i], envp, exit_status);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

static void	expand_args(t_cmd *cmd, char **envp, int exit_status)
{
	int	*had_quotes;

	if (!cmd || !cmd->args)
		return ;
	had_quotes = save_quote_markers(cmd->args, cmd->argc);
	do_expand_args(cmd, envp, exit_status);
	if (had_quotes)
	{
		remove_empty_unquoted_args(cmd, had_quotes);
		free(had_quotes);
	}
}

static void	expand_redirects(t_cmd *cmd, char **envp, int exit_status)
{
	t_redirect	*redir;
	char		*expanded;

	if (!cmd || !cmd->redirects)
		return ;
	redir = cmd->redirects;
	while (redir)
	{
		expanded = expand_string(redir->file, envp, exit_status);
		if (expanded)
		{
			free(redir->file);
			redir->file = expanded;
		}
		redir = redir->next;
	}
}
