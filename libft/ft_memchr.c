/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 04:50:06 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:17:20 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;

	ptr = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == ch)
			return (ptr);
		ptr++;
		n--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char str1[] = "Hello, World!";
// 	char str2[] = "Hello, World!";
// 	char *result1;
// 	char *result2;

// 	printf("Test 1 - Original strings:\n");
// 	printf("str1: %s\n", str1);
// 	printf("str2: %s\n\n", str2);

// 	// 'o'を検索（6文字目まで）
// 	result1 = ft_memchr(str1, 'o', 6);
// 	result2 = memchr(str2, 'o', 6);

// 	printf("Test 1 - Search Results:\n");
// 	if (result1)
// 		printf("ft_memchr found 'o' at position: %ld\n", result1 - str1);
// 	else
// 		printf("ft_memchr: Character not found\n");

// 	if (result2)
// 		printf("memchr found 'o' at position: %ld\n", result2 - str2);
// 	else
// 		printf("memchr: Character not found\n");

// 	// 存在しない文字を検索
// 	result1 = ft_memchr(str1, 'z', 13);
// 	result2 = memchr(str2, 'z', 13);

// 	printf("\nTest 2 - Searching for non-existent character:\n");
// 	if (result1)
// 		printf("ft_memchr: Character found\n");
// 	else
// 		printf("ft_memchr: Character not found\n");

// 	if (result2)
// 		printf("memchr: Character found\n");
// 	else
// 		printf("memchr: Character not found\n");

// 	return (0);
// }