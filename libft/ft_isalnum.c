/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:57:10 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:22:33 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0'
			&& c <= '9'))
		return (1);
	return (0);
}
// int	main(void)

// {
// 	printf("%d", ft_isalnum('A'));
// 	printf("%d", ft_isalnum('b'));
// 	printf("%d", ft_isalnum('0'));
// 	printf("%d", ft_isalnum('8'));
// 	printf("%d", ft_isalnum('!'));
// 	return (0);
// }
