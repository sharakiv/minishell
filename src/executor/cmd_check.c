/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 07:32:50 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/09 07:32:54 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"
#include <sys/stat.h>

static int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0)
		return (S_ISDIR(sb.st_mode));
	return (0);
}

static void	print_cmd_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

int	check_path_error(char *cmd)
{
	if (access(cmd, F_OK) != 0)
	{
		print_cmd_error(cmd, "No such file or directory");
		return (127);
	}
	if (is_directory(cmd))
	{
		print_cmd_error(cmd, "Is a directory");
		return (126);
	}
	if (access(cmd, X_OK) != 0)
	{
		print_cmd_error(cmd, "Permission denied");
		return (126);
	}
	return (0);
}

void	print_not_found_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*handle_direct_path(char *cmd)
{
	int	error_code;

	error_code = check_path_error(cmd);
	if (error_code != 0)
		exit(error_code);
	return (ft_strdup(cmd));
}
