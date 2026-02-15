/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 01:55:26 by sharaki           #+#    #+#             */
/*   Updated: 2025/12/06 04:29:16 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"

static int	skip_whitespace_and_sign(char *str, int *sign);
static int	compare_overflow(char *str, int len, int sign);

int	check_overflow(char *str)
{
	int	i;
	int	start;
	int	sign;
	int	len;

	i = skip_whitespace_and_sign(str, &sign);
	while (str[i] == '0')
		i++;
	start = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	len = i - start;
	return (compare_overflow(str + start, len, sign));
}

static int	skip_whitespace_and_sign(char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	*sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

static int	compare_overflow(char *str, int len, int sign)
{
	char	*max;
	char	*min;

	max = "9223372036854775807";
	min = "9223372036854775808";
	if (len > 19)
		return (1);
	if (len < 19)
		return (0);
	if (sign == 1 && ft_strncmp(str, max, 19) > 0)
		return (1);
	if (sign == -1 && ft_strncmp(str, min, 19) > 0)
		return (1);
	return (0);
}
