/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 22:27:42 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 08:16:13 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

int	is_same_string(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (1);
	return (0);
}

char	*expand_heredoc_line(char *input, int expand_var, t_shell *shell)
{
	char	*expanded;

	if (!expand_var || !shell)
		return (input);
	expanded = expand_string(input, shell->envp, shell->exit_status);
	free(input);
	return (expanded);
}

void	write_heredoc_line(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
}

void	cleanup_child(t_shell *shell)
{
	if (shell->tokens)
		free_token_list(shell->tokens);
	if (shell->cmd)
		free_cmd_list(shell->cmd);
	shell->tokens = NULL;
	shell->cmd = NULL;
}
