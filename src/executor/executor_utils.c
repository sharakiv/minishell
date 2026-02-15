/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 16:40:34 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 09:35:19 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	get_exit_status(int status)
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
	return (1);
}

void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static int	setup_heredoc_redirect(t_cmd *cmd, t_shell *shell)
{
	int	heredoc_fd;

	if (!cmd->heredocs)
		return (1);
	heredoc_fd = read_all_heredocs(cmd, shell);
	if (heredoc_fd == -1)
		return (0);
	if (dup2(heredoc_fd, STDIN_FILENO) == -1)
	{
		close(heredoc_fd);
		return (0);
	}
	close(heredoc_fd);
	return (1);
}

int	execute_builtin_with_redirect(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	result;

	saved_stdin = dup(STDIN_FILENO);
	if (saved_stdin == -1)
		return (1);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == -1)
	{
		close(saved_stdin);
		return (1);
	}
	if (!setup_heredoc_redirect(cmd, shell) || !apply_redirections(cmd))
	{
		restore_std_fds(saved_stdin, saved_stdout);
		return (1);
	}
	result = execute_builtin(cmd, shell);
	restore_std_fds(saved_stdin, saved_stdout);
	return (result);
}

void	execute_external_command(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	check_empty_command(cmd, shell);
	if (ft_strchr(cmd->args[0], '/'))
	{
		handle_path_error(cmd->args[0], shell);
		path = cmd->args[0];
	}
	else
	{
		path = find_command_path(cmd->args[0], shell->envp);
		if (!path)
			print_cmd_not_found(cmd->args[0], shell);
	}
	execve(path, cmd->args, shell->envp);
	perror(cmd->args[0]);
	if (path != cmd->args[0])
		free(path);
	child_exit(shell, 127);
}
