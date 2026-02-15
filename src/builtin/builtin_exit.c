/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 18:04:59 by kteranis          #+#    #+#             */
/*   Updated: 2025/12/20 15:58:50 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	is_valid_number(char *str);
int			check_overflow(char *str);
static void	print_numeric_error(char *arg);
static long	ft_atol_exit(char *str);

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	long	exit_code;

	if (!cmd->in_pipeline)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	if (cmd->argc == 1)
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!is_valid_number(cmd->args[1]) || check_overflow(cmd->args[1]))
	{
		print_numeric_error(cmd->args[1]);
		shell->should_exit = 1;
		return (2);
	}
	if (cmd->argc > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	exit_code = ft_atol_exit(cmd->args[1]);
	shell->should_exit = 1;
	return ((unsigned char)exit_code);
}

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
}

static long	ft_atol_exit(char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			{
				while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
					i++;
				return (str[i] == '\0');
			}
			return (0);
		}
		i++;
	}
	return (1);
}
