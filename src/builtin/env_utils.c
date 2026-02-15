/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:21:08 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/06 03:36:18 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i])
		i++;
	return (i);
}

void	free_envp(char **envp)
{
	int	i;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

char	**get_envp(char **envp)
{
	int		i;
	int		envp_num;
	char	**shell_envp;

	envp_num = count_envp(envp);
	shell_envp = malloc(sizeof(char *) * (envp_num + 1));
	if (!shell_envp)
	{
		perror("minishell: fail to initialize environment");
		return (NULL);
	}
	i = 0;
	while (i < envp_num)
	{
		shell_envp[i] = ft_strdup(envp[i]);
		if (!shell_envp[i])
		{
			free_envp(shell_envp);
			return (NULL);
		}
		i++;
	}
	shell_envp[i] = NULL;
	return (shell_envp);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	find_env_index(char **envp, char *name)
{
	int		i;
	size_t	len;

	if (!envp || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
