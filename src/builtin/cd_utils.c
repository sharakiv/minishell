/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 04:15:35 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/06 04:15:49 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static char	*create_env_entry(char *name, char *value)
{
	char	*entry;
	char	*temp;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	entry = ft_strjoin(temp, value);
	free(temp);
	return (entry);
}

static int	find_env_index_by_name(char **envp, char *name)
{
	int	i;
	int	len;

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

static int	add_new_env_var(char *name, char *value, t_shell *shell)
{
	char	**new_envp;
	char	*entry;
	int		i;

	i = 0;
	while (shell->envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (1);
	i = 0;
	while (shell->envp[i])
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	entry = create_env_entry(name, value);
	if (!entry)
		return (free(new_envp), 1);
	new_envp[i] = entry;
	new_envp[i + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int	set_env_var(char *name, char *value, t_shell *shell)
{
	int		index;
	char	*new_entry;

	if (!name || !value || !shell || !shell->envp)
		return (1);
	index = find_env_index_by_name(shell->envp, name);
	if (index >= 0)
	{
		new_entry = create_env_entry(name, value);
		if (!new_entry)
			return (1);
		free(shell->envp[index]);
		shell->envp[index] = new_entry;
		return (0);
	}
	return (add_new_env_var(name, value, shell));
}
