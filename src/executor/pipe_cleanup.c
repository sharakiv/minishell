/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 18:44:50 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:57:38 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	count_pipe(t_cmd *cmd)
{
	int	cmd_count;

	cmd_count = count_commands(cmd);
	if (cmd_count > 0)
		return (cmd_count - 1);
	return (0);
}

static void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	handle_pipe_error(t_cmd *cmd, t_pipe_ctx *ctx)
{
	close_pipeline_heredocs(cmd);
	if (ctx)
		free_pipes(ctx->pipes, ctx->pipe_count);
	setup_signal_handlers();
	return (1);
}

int	finish_pipeline(t_pipe_ctx *ctx, pid_t *pids, t_cmd *cmd)
{
	int	exit_status;

	close_all_pipes(ctx->pipes, ctx->pipe_count);
	close_pipeline_heredocs(cmd);
	exit_status = wait_all_children(pids, ctx->pipe_count + 1);
	setup_signal_handlers();
	cleanup_pipes_and_pids(ctx->pipes, pids, ctx->pipe_count);
	return (exit_status);
}
