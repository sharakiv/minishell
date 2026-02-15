/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:27:12 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/09 07:04:37 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

void		heredoc_child(t_heredoc *heredoc, int write_fd, t_shell *shell);
int			wait_heredoc_child(pid_t pid, int *pipefd);

static int	handle_fork_fail(int *pipefd, struct termios *saved)
{
	close(pipefd[0]);
	close(pipefd[1]);
	tcsetattr(STDIN_FILENO, TCSANOW, saved);
	return (-1);
}

int	read_heredoc(t_heredoc *heredoc, t_shell *shell)
{
	int				pipefd[2];
	pid_t			pid;
	struct termios	saved_term;
	int				result;

	if (pipe(pipefd) == -1)
		return (-1);
	tcgetattr(STDIN_FILENO, &saved_term);
	setup_signal_ignore();
	pid = fork();
	if (pid == -1)
		return (handle_fork_fail(pipefd, &saved_term));
	if (pid == 0)
	{
		close(pipefd[0]);
		heredoc_child(heredoc, pipefd[1], shell);
	}
	close(pipefd[1]);
	result = wait_heredoc_child(pid, pipefd);
	tcsetattr(STDIN_FILENO, TCSANOW, &saved_term);
	return (result);
}

int	read_all_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_heredoc	*current;
	int			fd;

	current = cmd->heredocs;
	fd = -1;
	while (current != NULL)
	{
		if (fd != -1)
			close(fd);
		fd = read_heredoc(current, shell);
		if (fd == -2)
		{
			shell->exit_status = 130;
			setup_signal_handlers();
			return (-1);
		}
		if (fd < 0)
			return (setup_signal_handlers(), -1);
		current = current->next;
	}
	setup_signal_handlers();
	return (fd);
}

int	read_pipeline_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->heredocs)
		{
			current->heredoc_fd = read_all_heredocs(current, shell);
			if (current->heredoc_fd == -1)
			{
				close_pipeline_heredocs(cmd);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

void	close_pipeline_heredocs(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->heredoc_fd != -1)
		{
			close(current->heredoc_fd);
			current->heredoc_fd = -1;
		}
		current = current->next;
	}
}
