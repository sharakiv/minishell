/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 08:02:53 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 12:34:24 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"
#include <sys/stat.h>

void	child_exit(t_shell *shell, int code)
{
	cleanup_child(shell);
	free_envp(shell->envp);
	exit(code);
}

static void	print_exec_error(char *cmd, char *msg, int code, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	child_exit(shell, code);
}

void	handle_path_error(char *cmd, t_shell *shell)
{
	struct stat	st;

	if (stat(cmd, &st) == -1)
	{
		if (errno == ENOTDIR)
			print_exec_error(cmd, "Not a directory", 126, shell);
		else
			print_exec_error(cmd, "No such file or directory", 127, shell);
	}
	if (S_ISDIR(st.st_mode))
		print_exec_error(cmd, "Is a directory", 126, shell);
	if (access(cmd, X_OK) == -1)
		print_exec_error(cmd, "Permission denied", 126, shell);
}

void	print_cmd_not_found(char *cmd, t_shell *shell)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	child_exit(shell, 127);
}

void	check_empty_command(t_cmd *cmd, t_shell *shell)
{
	if (!cmd->args[0] || cmd->args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: : command not found\n", 2);
		child_exit(shell, 127);
	}
}
