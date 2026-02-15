/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:28:04 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/20 09:53:44 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

volatile sig_atomic_t	g_signal_number = 0;
static int				shell_loop(t_shell *shell);

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.envp = get_envp(envp);
	if (!shell.envp)
		return (1);
	shell.exit_status = 0;
	shell.should_exit = 0;
	shell.tokens = NULL;
	shell.cmd = NULL;
	setup_signal_handlers();
	shell.exit_status = shell_loop(&shell);
	free_envp(shell.envp);
	return (shell.exit_status);
}

static int	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (g_signal_number != 0)
		{
			shell->exit_status = 128 + g_signal_number;
			g_signal_number = 0;
		}
		if (!input)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			return (shell->exit_status);
		}
		if (*input)
		{
			add_history(input);
			shell->exit_status = process_input(input, shell);
		}
		free(input);
		if (shell->should_exit)
			return (shell->exit_status);
	}
}
