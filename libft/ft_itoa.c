/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:41:38 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:22:53 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int		len;
	long	num;

	len = 1;
	if (n < 0)
		len++;
	num = (long)n;
	if (num < 0)
		num = -num;
	while (num > 9)
	{
		len++;
		num = num / 10;
	}
	return (len);
}

static void	convert_to_str(int n, char *str, int len)
{
	long	num;

	num = (long)n;
	if (num < 0)
		num = -num;
	while (len > 0)
	{
		len--;
		str[len] = '0' + (num % 10);
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	len = count_digits(n);
	result = malloc(sizeof(char) * (len + 1));
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	convert_to_str(n, result, len);
	return (result);
}
