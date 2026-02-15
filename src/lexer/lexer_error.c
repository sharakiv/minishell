/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 00:30:01 by sharaki           #+#    #+#             */
/*   Updated: 2025/06/25 22:40:21 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include "../../libft/libft.h"

void	write_syntax_error(char *token)
{
	char	*prefix;
	char	*suffix;

	prefix = "minishell: syntax error near unexpected token `";
	suffix = "'\n";
	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

void	write_syntax_error_with_input(char *token, char *original_input)
{
	char	*prefix;
	char	*suffix;

	prefix = "minishell: syntax error near unexpected token `";
	suffix = "'\n";
	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, suffix, ft_strlen(suffix));
	write(STDERR_FILENO, "minishell: `", 13);
	write(STDERR_FILENO, original_input, ft_strlen(original_input));
	write(STDERR_FILENO, "'\n", 2);
}
