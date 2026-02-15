/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:29:11 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 13:16:38 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static char	*build_expanded_string(char *before, char *value, char *after);
static int	process_char(char **result, int i, char **envp, int exit_status);

char	*expand_string(char *str, char **envp, int exit_status)
{
	int		i;
	char	*result;
	char	*temp;

	if (!str)
		return (NULL);
	result = ft_strdup(str);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i])
	{
		i = process_char(&result, i, envp, exit_status);
		if (i < 0)
			return (NULL);
	}
	temp = remove_markers(result);
	free(result);
	return (temp);
}

static int	process_char(char **result, int i, char **envp, int exit_status)
{
	char	*temp;

	if ((*result)[i] == '\x01' && (*result)[i + 1] == '$')
		temp = remove_char_at(*result, i);
	else if ((*result)[i] == '$')
		temp = expand_variable(*result, i, envp, exit_status);
	else
		return (i + 1);
	free(*result);
	*result = temp;
	if (!*result)
		return (-1);
	if ((*result)[i] == '$')
		return (i + 1);
	return (i);
}

char	*expand_variable(char *str, int pos, char **envp, int exit_status)
{
	char	*var_name;
	char	*value;
	char	*before;
	char	*after;
	char	*result;

	var_name = get_var_name(str, pos);
	if (!var_name || var_name[0] == '\0')
	{
		free(var_name);
		return (ft_strdup(str));
	}
	if (var_name[0] == '?' && var_name[1] == '\0')
		value = ft_itoa(exit_status);
	else
		value = get_env_value(var_name, envp);
	before = ft_substr(str, 0, pos);
	after = ft_strdup(str + pos + 1 + ft_strlen(var_name));
	result = build_expanded_string(before, value, after);
	free(var_name);
	free(value);
	free(before);
	free(after);
	return (result);
}

static char	*build_expanded_string(char *before, char *value, char *after)
{
	char	*temp;
	char	*result;

	if (!before || !after)
		return (NULL);
	if (!value)
		value = "";
	temp = ft_strjoin(before, value);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, after);
	free(temp);
	return (result);
}
