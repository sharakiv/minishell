/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:37:05 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 06:12:40 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// int	main(void)
// {
// 	printf("%c\n", ft_tolower('a'));
// 	printf("%c\n", ft_tolower('z'));
// 	printf("%c\n", ft_tolower('A'));
// 	printf("%c\n", ft_tolower('Z'));
// 	printf("%c\n", ft_tolower('$'));
// 	printf("%c\n", ft_tolower('6'));
// 	return (0);
// }
