/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 08:16:02 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:16:50 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	has_quote_marker(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\x02')
			return (1);
		str++;
	}
	return (0);
}

static int	count_non_empty_args(char **args, int *had_quotes)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (args[i])
	{
		if (args[i][0] != '\0' || had_quotes[i])
			count++;
		i++;
	}
	return (count);
}

static void	copy_valid_args(t_cmd *cmd, char **new_args, int *had_quotes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] != '\0' || had_quotes[i])
		{
			new_args[j] = cmd->args[i];
			j++;
		}
		else
			free(cmd->args[i]);
		i++;
	}
	new_args[j] = NULL;
	free(cmd->args);
	cmd->args = new_args;
	cmd->argc = j;
}

void	remove_empty_unquoted_args(t_cmd *cmd, int *had_quotes)
{
	char	**new_args;
	int		new_count;

	if (!cmd || !cmd->args || !had_quotes)
		return ;
	new_count = count_non_empty_args(cmd->args, had_quotes);
	new_args = malloc(sizeof(char *) * (new_count + 1));
	if (!new_args)
		return ;
	copy_valid_args(cmd, new_args, had_quotes);
}

int	*save_quote_markers(char **args, int argc)
{
	int	*had_quotes;
	int	i;

	had_quotes = malloc(sizeof(int) * argc);
	if (!had_quotes)
		return (NULL);
	i = 0;
	while (i < argc)
	{
		had_quotes[i] = has_quote_marker(args[i]);
		i++;
	}
	return (had_quotes);
}
