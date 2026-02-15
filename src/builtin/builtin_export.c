/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 12:00:00 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/06 04:25:35 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

void		print_sorted_export(t_shell *shell);
static void	print_export_error(char *arg);
static int	process_with_equal(char *arg, t_shell *shell);
static int	process_export_arg(char *arg, t_shell *shell);

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	status;

	if (cmd->argc == 1)
	{
		print_sorted_export(shell);
		return (0);
	}
	status = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (process_export_arg(cmd->args[i], shell) != 0)
			status = 1;
		i++;
	}
	return (status);
}

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

static int	process_with_equal(char *arg, t_shell *shell)
{
	int	result;

	result = update_env_var(arg, shell->envp);
	if (result == 1)
		return (0);
	if (result == -1)
		return (1);
	return (add_env_var(arg, shell));
}

static int	process_export_arg(char *arg, t_shell *shell)
{
	if (!validate_export_name(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (!ft_strchr(arg, '='))
		return (0);
	return (process_with_equal(arg, shell));
}
