/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirection_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:56:12 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/07 20:52:35 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

t_redirect	*create_redirect(t_token_type type, char *file)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->file = ft_strdup(file);
	if (!redirect->file)
	{
		free(redirect);
		return (NULL);
	}
	redirect->next = NULL;
	return (redirect);
}

void	add_redirect_to_list(t_redirect **head, t_redirect *new_redirect)
{
	t_redirect	*current;

	if (!head || !new_redirect)
		return ;
	if (!*head)
	{
		*head = new_redirect;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_redirect;
}

int	handle_heredoc(t_cmd *cmd, t_token **tok)
{
	t_heredoc	*new_heredoc;
	int			expand_var;
	char		*content;

	if (!(*tok)->next || (*tok)->next->type != WORD)
		return (0);
	content = (*tok)->next->content;
	expand_var = (ft_strchr(content, '\x02') == NULL);
	new_heredoc = create_heredoc(content, expand_var);
	if (!new_heredoc)
		return (0);
	add_heredoc_to_list(&cmd->heredocs, new_heredoc);
	*tok = (*tok)->next;
	return (1);
}

t_heredoc	*create_heredoc(char *delimiter, int expand_var)
{
	t_heredoc	*heredoc;
	int			i;
	int			j;

	heredoc = malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delimiter = malloc(ft_strlen(delimiter) + 1);
	if (!heredoc->delimiter)
		return (free(heredoc), NULL);
	i = 0;
	j = 0;
	while (delimiter[i])
	{
		if (delimiter[i] != '\x01' && delimiter[i] != '\x02')
			heredoc->delimiter[j++] = delimiter[i];
		i++;
	}
	heredoc->delimiter[j] = '\0';
	heredoc->content = NULL;
	heredoc->expand_var = expand_var;
	heredoc->next = NULL;
	return (heredoc);
}

void	add_heredoc_to_list(t_heredoc **head, t_heredoc *new_heredoc)
{
	t_heredoc	*current;

	if (!head || !new_heredoc)
		return ;
	if (!*head)
	{
		*head = new_heredoc;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_heredoc;
}
