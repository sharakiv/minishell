/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:26:55 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:57:27 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	**create_pipes(int pipe_count)
{
	int	**pipes;
	int	i;

	pipes = malloc(sizeof(int *) * pipe_count);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			cleanup_pipes_malloc_error(pipes, i);
			return (NULL);
		}
		if (pipe(pipes[i]) == -1)
		{
			free(pipes[i]);
			cleanup_pipes_pipe_error(pipes, i);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	free_pipes_array(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	handle_child_in_pipeline(t_cmd *current, int cmd_index,
		t_pipe_ctx *ctx, pid_t *pids)
{
	setup_signal_default();
	setup_child_pipes(ctx->pipes, ctx->pipe_count, cmd_index);
	free(pids);
	free_pipes_array(ctx->pipes, ctx->pipe_count);
	execute_child_command(current, ctx->shell);
}

static void	handle_fork_failure(pid_t *pids, int forked, t_pipe_ctx *ctx)
{
	int	i;

	close_all_pipes(ctx->pipes, ctx->pipe_count);
	i = 0;
	while (i < forked)
	{
		kill(pids[i], SIGTERM);
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}

pid_t	*fork_commands(t_cmd *cmd, t_pipe_ctx *ctx)
{
	pid_t	*pids;
	t_cmd	*current;
	int		cmd_index;
	int		total_cmds;

	total_cmds = ctx->pipe_count + 1;
	pids = malloc(sizeof(pid_t) * total_cmds);
	if (!pids)
		return (NULL);
	current = cmd;
	cmd_index = 0;
	while (current)
	{
		pids[cmd_index] = fork();
		if (pids[cmd_index] == -1)
		{
			handle_fork_failure(pids, cmd_index, ctx);
			return (NULL);
		}
		if (pids[cmd_index] == 0)
			handle_child_in_pipeline(current, cmd_index, ctx, pids);
		current = current->next;
		cmd_index++;
	}
	return (pids);
}
