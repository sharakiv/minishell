/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:58:01 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 06:29:06 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (sign == 1 && (result > (LONG_MAX - (*nptr - '0')) / 10) && (*nptr
				- '0') >= 7)
			return ((int)LONG_MAX);
		if (sign == -1 && (result > (LONG_MIN - (*nptr - '0')) / 10) && (*nptr
				- '0') >= 8)
			return ((int)LONG_MIN);
		result = result * 10 + (*nptr - '0');
		nptr++;
	}
	return ((int)(result * sign));
}

// int	main(void)
// {
// 	printf("%d\n", atoi("2147483648"));
// 	printf("%d\n", atoi("-2147483649"));
// 	printf("%d\n", ft_atoi("-1000043"));
// 	printf("%d\n", ft_atoi("-2147483649"));
// 	return (0);
// }
