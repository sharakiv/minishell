/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 16:12:16 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:22:40 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
// int	main(void)

// {
// 	printf("%d", ft_isascii('A'));
// 	printf("%d", ft_isascii('1'));
// 	printf("%d", ft_isascii('2'));
// 	printf("%d", ft_isascii(128));
// 	printf("%d", ft_isascii(-4));
// 	return (0);
// }
