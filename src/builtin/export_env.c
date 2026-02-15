/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 02:38:21 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/06 02:38:29 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	validate_export_name(char *str)
{
	int	i;

	if (!str || !str[0] || str[0] == '=')
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

static int	get_name_len(char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (0);
	return (equal_pos - arg);
}

int	update_env_var(char *arg, char **envp)
{
	int		i;
	int		len;
	char	*new_val;

	len = get_name_len(arg);
	if (len == 0)
		return (0);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, len) == 0 && envp[i][len] == '=')
		{
			new_val = ft_strdup(arg);
			if (!new_val)
				return (-1);
			free(envp[i]);
			envp[i] = new_val;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

int	add_env_var(char *arg, t_shell *shell)
{
	char	**new_envp;
	int		count;
	int		i;

	count = count_env(shell->envp);
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (i < count)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[count] = ft_strdup(arg);
	if (!new_envp[count])
	{
		free(new_envp);
		return (1);
	}
	new_envp[count + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}
