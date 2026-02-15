/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 05:37:14 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:16:22 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	count_commands(t_cmd *cmd)
{
	int		cmd_num;
	t_cmd	*current;

	cmd_num = 0;
	current = cmd;
	if (!cmd)
		return (0);
	while (current)
	{
		cmd_num++;
		current = current->next;
	}
	return (cmd_num);
}

void	cleanup_pipes_malloc_error(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	cleanup_pipes_pipe_error(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

void	setup_child_pipes(int **pipes, int pipe_count, int cmd_index)
{
	int	i;

	if (cmd_index > 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < pipe_count)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute_child_command(t_cmd *current, t_shell *shell)
{
	int	status;

	if (current->heredoc_fd != -1)
	{
		dup2(current->heredoc_fd, STDIN_FILENO);
		close(current->heredoc_fd);
	}
	if (current->redirects && !apply_redirections(current))
	{
		cleanup_child(shell);
		free_envp(shell->envp);
		exit(1);
	}
	if (is_builtin(current))
	{
		status = execute_builtin(current, shell);
		cleanup_child(shell);
		free_envp(shell->envp);
		exit(status);
	}
	execute_external_command(current, shell);
}
