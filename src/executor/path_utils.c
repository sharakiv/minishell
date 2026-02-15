/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 05:21:11 by sharaki           #+#    #+#             */
/*   Updated: 2025/09/28 05:21:45 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	count_paths(const char *path_env)
{
	int	count;
	int	i;

	if (!path_env || !*path_env)
		return (0);
	count = 1;
	i = 0;
	while (path_env[i])
	{
		if (path_env[i] == ':')
			count++;
		i++;
	}
	return (count);
}

char	*extract_path(const char *path_env, int *index)
{
	int		start;
	int		len;
	char	*path;

	start = *index;
	len = 0;
	while (path_env[*index] && path_env[*index] != ':')
	{
		(*index)++;
		len++;
	}
	if (len == 0)
		return (ft_strdup("."));
	path = malloc(len + 1);
	if (!path)
		return (NULL);
	ft_memcpy(path, &path_env[start], len);
	path[len] = '\0';
	if (path_env[*index] == ':')
		(*index)++;
	return (path);
}

char	*build_full_path(const char *dir, const char *cmd)
{
	char	*full_path;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = malloc(len);
	if (!full_path)
		return (NULL);
	full_path[0] = '\0';
	ft_strlcat(full_path, dir, len);
	ft_strlcat(full_path, "/", len);
	ft_strlcat(full_path, cmd, len);
	return (full_path);
}

void	free_path_array(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}
