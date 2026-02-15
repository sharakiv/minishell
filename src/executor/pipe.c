/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 05:03:40 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 15:57:14 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	t_pipe_ctx	ctx;
	pid_t		*pids;
	t_cmd		*current;

	current = cmd;
	while (current)
	{
		current->in_pipeline = 1;
		current = current->next;
	}
	if (!read_pipeline_heredocs(cmd, shell))
		return (130);
	ctx.pipe_count = count_pipe(cmd);
	ctx.pipes = create_pipes(ctx.pipe_count);
	ctx.shell = shell;
	if (!ctx.pipes)
		return (handle_pipe_error(cmd, NULL));
	setup_signal_ignore();
	pids = fork_commands(cmd, &ctx);
	if (!pids)
		return (handle_pipe_error(cmd, &ctx));
	return (finish_pipeline(&ctx, pids, cmd));
}

static int	get_last_cmd_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		return (128 + WTERMSIG(status));
	}
	return (0);
}

void	close_all_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	wait_all_children(pid_t *pids, int total_cmds)
{
	int	i;
	int	status;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < total_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (i == total_cmds - 1)
			exit_status = get_last_cmd_status(status);
		i++;
	}
	return (exit_status);
}

void	cleanup_pipes_and_pids(int **pipes, pid_t *pids, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
	free(pids);
}
