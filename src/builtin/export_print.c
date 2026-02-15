/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 19:20:52 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/06 02:37:44 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static char	**copy_env_array(char **envp)
{
	char	**copy;
	int		count;
	int		i;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		copy[i] = envp[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	sort_env_copy(char **env_copy)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env_copy[i])
	{
		j = i + 1;
		while (env_copy[j])
		{
			if (ft_strncmp(env_copy[i], env_copy[j], ft_strlen(env_copy[i])
					+ ft_strlen(env_copy[j])) > 0)
			{
				tmp = env_copy[i];
				env_copy[i] = env_copy[j];
				env_copy[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_with_value(char *env_str, char *equal_pos)
{
	int	name_len;

	name_len = equal_pos - env_str;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	write(STDOUT_FILENO, env_str, name_len);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(equal_pos + 1, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

static void	print_declare_line(char *env_str)
{
	char	*equal_pos;

	equal_pos = ft_strchr(env_str, '=');
	if (equal_pos)
		print_with_value(env_str, equal_pos);
	else
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(env_str, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}

void	print_sorted_export(t_shell *shell)
{
	char	**env_copy;
	int		i;

	if (!shell || !shell->envp)
		return ;
	env_copy = copy_env_array(shell->envp);
	if (!env_copy)
		return ;
	sort_env_copy(env_copy);
	i = 0;
	while (env_copy[i])
	{
		print_declare_line(env_copy[i]);
		i++;
	}
	free(env_copy);
}
