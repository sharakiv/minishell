/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 06:20:13 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 10:00:09 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static void	heredoc_child_exit(int write_fd, t_shell *shell, int code);
static void	handle_heredoc_eof(int write_fd, char *delim, t_shell *shell);
static void	print_heredoc_eof_warning(char *delimiter);

void	heredoc_child(t_heredoc *heredoc, int write_fd, t_shell *shell)
{
	char	*input;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("> ");
		if (!input)
			handle_heredoc_eof(write_fd, heredoc->delimiter, shell);
		if (is_same_string(input, heredoc->delimiter))
		{
			free(input);
			break ;
		}
		input = expand_heredoc_line(input, heredoc->expand_var, shell);
		if (!input)
			heredoc_child_exit(write_fd, shell, 1);
		write_heredoc_line(write_fd, input);
	}
	heredoc_child_exit(write_fd, shell, 0);
}

static void	heredoc_child_exit(int write_fd, t_shell *shell, int code)
{
	close(write_fd);
	cleanup_child(shell);
	free_envp(shell->envp);
	exit(code);
}

static void	handle_heredoc_eof(int write_fd, char *delimiter, t_shell *shell)
{
	print_heredoc_eof_warning(delimiter);
	heredoc_child_exit(write_fd, shell, 0);
}

static void	print_heredoc_eof_warning(char *delimiter)
{
	ft_putstr_fd("minishell: warning: ", STDERR_FILENO);
	ft_putstr_fd("here-document delimited by end-of-file ", STDERR_FILENO);
	ft_putstr_fd("(wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int	wait_heredoc_child(pid_t pid, int *pipefd)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		close(pipefd[0]);
		return (-2);
	}
	return (pipefd[0]);
}
