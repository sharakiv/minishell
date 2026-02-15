/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:36:57 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:16:33 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	executor(t_cmd *cmd, t_shell *shell)
{
	int	pipe_count;

	if (!cmd)
		return (1);
	pipe_count = count_pipe(cmd);
	if (pipe_count == 0)
		return (execute_single_command(cmd, shell));
	else
		return (execute_pipeline(cmd, shell));
}

static int	handle_redirect_only(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	heredoc_fd;
	int	result;

	heredoc_fd = -1;
	if (cmd->heredocs)
	{
		heredoc_fd = read_all_heredocs(cmd, shell);
		if (heredoc_fd == -1)
			return (shell->exit_status);
	}
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
		return (close(heredoc_fd), 1);
	if (heredoc_fd != -1)
	{
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	result = !apply_redirections(cmd);
	restore_std_fds(saved_stdin, saved_stdout);
	return (result);
}

static void	handle_child_process(t_cmd *cmd, int heredoc_fd, t_shell *shell)
{
	setup_signal_default();
	if (heredoc_fd != -1)
	{
		if (dup2(heredoc_fd, STDIN_FILENO) == -1)
		{
			cleanup_child(shell);
			free_envp(shell->envp);
			exit(EXIT_FAILURE);
		}
		close(heredoc_fd);
	}
	if (!apply_redirections(cmd))
	{
		cleanup_child(shell);
		free_envp(shell->envp);
		exit(EXIT_FAILURE);
	}
	execute_external_command(cmd, shell);
	cleanup_child(shell);
	free_envp(shell->envp);
	exit(EXIT_FAILURE);
}

static int	handle_fork_error(int heredoc_fd)
{
	perror("fork");
	if (heredoc_fd != -1)
		close(heredoc_fd);
	setup_signal_handlers();
	return (1);
}

int	execute_single_command(t_cmd *cmd, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		heredoc_fd;

	if (!cmd->args || !cmd->args[0])
		return (handle_redirect_only(cmd, shell));
	if (is_builtin(cmd))
		return (execute_builtin_with_redirect(cmd, shell));
	heredoc_fd = read_all_heredocs(cmd, shell);
	if (heredoc_fd == -1 && cmd->heredocs)
		return (shell->exit_status);
	setup_signal_ignore();
	pid = fork();
	if (pid == -1)
		return (handle_fork_error(heredoc_fd));
	if (pid == 0)
		handle_child_process(cmd, heredoc_fd, shell);
	if (heredoc_fd != -1)
		close(heredoc_fd);
	waitpid(pid, &status, 0);
	status = get_exit_status(status);
	setup_signal_handlers();
	return (status);
}
