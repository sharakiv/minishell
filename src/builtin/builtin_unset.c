/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 03:26:55 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 12:38:43 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	find_and_remove(char *arg, char **envp);
static int	is_valid_unset_name(char *str);
static void	remove_env_var(char **envp, int index);

int	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	ret;

	if (cmd->argc == 1)
		return (0);
	ret = 0;
	i = 1;
	while (cmd->args[i])
	{
		if (find_and_remove(cmd->args[i], shell->envp) != 0)
			ret = 1;
		i++;
	}
	return (ret);
}

static int	find_and_remove(char *arg, char **envp)
{
	int	i;
	int	name_len;
	int	match;

	if (!is_valid_unset_name(arg))
		return (0);
	name_len = 0;
	while (arg[name_len] && arg[name_len] != '=')
		name_len++;
	i = -1;
	while (envp[++i])
	{
		match = (ft_strncmp(envp[i], arg, name_len) == 0
				&& (envp[i][name_len] == '=' || envp[i][name_len] == '\0'));
		if (match)
			return (remove_env_var(envp, i), 0);
	}
	return (0);
}

static int	is_valid_unset_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_var(char **envp, int index)
{
	free(envp[index]);
	while (envp[index])
	{
		envp[index] = envp[index + 1];
		index++;
	}
}
