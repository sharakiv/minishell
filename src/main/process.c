/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 21:28:46 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 09:03:46 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	is_empty_input(char *input);
static int	execute_and_cleanup(t_token *tokens, t_cmd *cmd, t_shell *shell);

int	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = NULL;
	lexer(input, &tokens);
	if (!tokens)
	{
		if (is_empty_input(input))
			return (shell->exit_status);
		return (2);
	}
	cmd = parse_pipeline(tokens);
	if (!cmd)
	{
		free_token_list(tokens);
		return (2);
	}
	return (execute_and_cleanup(tokens, cmd, shell));
}

static int	is_empty_input(char *input)
{
	while (*input)
	{
		if (*input != ' ' && *input != '\t' && *input != '\n')
			return (0);
		input++;
	}
	return (1);
}

static int	execute_and_cleanup(t_token *tokens, t_cmd *cmd, t_shell *shell)
{
	shell->tokens = tokens;
	shell->cmd = cmd;
	expand_cmd_list(cmd, shell->envp, shell->exit_status);
	shell->exit_status = executor(cmd, shell);
	free_token_list(tokens);
	free_cmd_list(cmd);
	shell->tokens = NULL;
	shell->cmd = NULL;
	return (shell->exit_status);
}
