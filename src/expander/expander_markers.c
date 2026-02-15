/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_markers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 07:23:49 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/09 00:17:15 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

char	*remove_char_at(char *str, int pos)
{
	char	*before;
	char	*after;
	char	*result;

	before = ft_substr(str, 0, pos);
	after = ft_strdup(str + pos + 1);
	if (!before || !after)
	{
		free(before);
		free(after);
		return (NULL);
	}
	result = ft_strjoin(before, after);
	free(before);
	free(after);
	return (result);
}

char	*remove_markers(char *str)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\x02')
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
