/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:23:47 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/05 17:25:10 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (builtin_echo(cmd));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (builtin_cd(cmd, shell));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (builtin_export(cmd, shell));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		return (builtin_unset(cmd, shell));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (builtin_env(cmd, shell));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (builtin_exit(cmd, shell));
	return (1);
}
