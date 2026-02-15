/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 03:37:13 by sharaki           #+#    #+#             */
/*   Updated: 2025/09/29 13:39:40 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static char	*search_in_dirs(char **dirs, char *cmd);

static char	*search_current_dir(char *cmd)
{
	char	*path;

	path = build_full_path(".", cmd);
	if (path && access(path, X_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**dirs;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = get_env_value("PATH", envp);
	if (!path_env)
		return (search_current_dir(cmd));
	dirs = split_path(path_env);
	free(path_env);
	if (!dirs)
		return (NULL);
	return (search_in_dirs(dirs, cmd));
}

char	**split_path(const char *path_env)
{
	char	**paths;
	int		count;
	int		i;
	int		index;

	if (!path_env)
		return (NULL);
	count = count_paths(path_env);
	paths = ft_calloc(count + 1, sizeof(char *));
	if (!paths)
		return (NULL);
	i = 0;
	index = 0;
	while (i < count)
	{
		paths[i] = extract_path(path_env, &index);
		if (!paths[i])
		{
			free_path_array(paths);
			return (NULL);
		}
		i++;
	}
	paths[count] = NULL;
	return (paths);
}

static char	*search_in_dirs(char **dirs, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (dirs[i])
	{
		full_path = build_full_path(dirs[i], cmd);
		if (!full_path)
		{
			free_path_array(dirs);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			free_path_array(dirs);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_path_array(dirs);
	return (NULL);
}
