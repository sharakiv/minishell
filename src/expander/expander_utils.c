/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:28:52 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/07 03:32:19 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	is_special_var_char(char c)
{
	return (c == '?' || c == '@' || c == '*' || c == '#' || c == '$');
}

static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*get_var_name(char *str, int start)
{
	int		len;
	int		i;
	char	*var_name;

	if (!str || str[start] != '$')
		return (NULL);
	if (is_special_var_char(str[start + 1]))
		return (ft_substr(str, start + 1, 1));
	if (ft_isdigit(str[start + 1]))
		return (ft_substr(str, start + 1, 1));
	i = start + 1;
	len = 0;
	while (str[i] && is_valid_var_char(str[i]))
	{
		len++;
		i++;
	}
	if (len == 0)
		return (ft_strdup(""));
	var_name = ft_substr(str, start + 1, len);
	return (var_name);
}

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	int		len;
	char	*value;

	if (!var_name || !envp)
		return (NULL);
	len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
		{
			value = ft_strdup(envp[i] + len + 1);
			return (value);
		}
		i++;
	}
	return (NULL);
}
