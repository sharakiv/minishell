/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:41:53 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:22:44 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)

{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}

// int	main(void)
// {
// 	printf("%d", ft_isdigit('A'));
// 	printf("%d", ft_isdigit('0'));
// 	printf("%d", ft_isdigit('1'));
// 	printf("%d", ft_isdigit('2'));
// 	printf("%d", ft_isdigit('4'));
// 	printf("%d", ft_isdigit('9'));
// 	printf("%d", ft_isdigit('?'));
// 	return (0);
// }
