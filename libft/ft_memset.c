/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 00:40:49 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:16:31 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = (unsigned char)c;
		ptr++;
		n--;
	}
	return (s);
}

// int	main(void)
// {
// 	char str1[] = "Hello,World!";
// 	printf("Test1-string:\n");
// 	printf("Before:%s\n", str1);
// 	ft_memset(str1, 'X', 5);
// 	printf("After:%s\n\n", str1);

// 	char str2[] = "Hello,World!";
// 	printf("Test2-string:\n");
// 	printf("Before:%s\n", str2);
// 	memset(str2, 'X', 5);
// 	printf("After:%s\n", str2);
// 	return (0);
// }