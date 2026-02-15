/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 20:56:26 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 10:01:53 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	count_args_correctly(t_token *start, t_token *end)
{
	t_token	*tok;
	int		count;
	int		skip_next;

	count = 0;
	skip_next = 0;
	tok = start;
	while (tok && tok != end)
	{
		if (skip_next)
			skip_next = 0;
		else if (is_redirect_token(tok->type) || tok->type == TOKEN_HEREDOC)
			skip_next = 1;
		else if (tok->type == WORD)
			count++;
		tok = tok->next;
	}
	return (count);
}

static int	handle_redirect(t_cmd *cmd, t_token **tok)
{
	t_redirect	*new_redirect;

	if (!(*tok)->next || (*tok)->next->type != WORD)
		return (0);
	new_redirect = create_redirect((*tok)->type, (*tok)->next->content);
	if (!new_redirect)
		return (0);
	add_redirect_to_list(&cmd->redirects, new_redirect);
	*tok = (*tok)->next;
	return (1);
}

static int	process_word(t_cmd *cmd, t_token *tok, int *i)
{
	if (!cmd->args)
		return (1);
	cmd->args[*i] = ft_strdup(tok->content);
	if (!cmd->args[*i])
		return (0);
	cmd->quote_types[(*i)++] = tok->quote_type;
	return (1);
}

static int	process_tokens(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*tok;
	int		i;

	tok = start;
	i = 0;
	while (tok && tok != end)
	{
		if (is_redirect_token(tok->type))
		{
			if (!handle_redirect(cmd, &tok))
				return (0);
		}
		else if (tok->type == TOKEN_HEREDOC)
		{
			if (!handle_heredoc(cmd, &tok))
				return (0);
		}
		else if (tok->type == WORD && !process_word(cmd, tok, &i))
			return (0);
		tok = tok->next;
	}
	cmd->argc = i;
	return (1);
}

t_cmd	*parse_single_command(t_token *start, t_token *end)
{
	t_cmd	*cmd;
	int		word_count;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	word_count = count_args_correctly(start, end);
	if (word_count > 0)
	{
		cmd->args = ft_calloc(word_count + 1, sizeof(char *));
		if (!cmd->args)
			return (cleanup_cmd(cmd), NULL);
		cmd->quote_types = ft_calloc(word_count + 1, sizeof(t_quote_type));
		if (!cmd->quote_types)
			return (cleanup_cmd(cmd), NULL);
	}
	if (!process_tokens(cmd, start, end))
		return (cleanup_cmd(cmd), NULL);
	return (cmd);
}
