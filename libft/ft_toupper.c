/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:24:15 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 06:12:32 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// int	main(void)
// {
// 	printf("%c\n", ft_toupper('a'));
// 	printf("%c\n", ft_toupper('d'));
// 	printf("%c\n", ft_toupper('A'));
// 	printf("%c\n", ft_toupper('Z'));
// 	printf("%c\n", ft_toupper('8'));
// 	printf("%c\n", ft_toupper('$'));
// 	return (0);
// }
