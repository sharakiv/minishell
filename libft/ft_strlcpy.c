/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:37:00 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:14:57 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char src[] = "Hello, World!"; // コピー元文字列
// 	char dst[20];                 // コピー先バッファ
// 	size_t result;                // 関数の戻り値を保存

// 	// テストケース1: 通常のコピー
// 	result = ft_strlcpy(dst, src, sizeof(dst));
// 	printf("Test1 - Normal Copy:\n");
// 	printf("src: %s\n", src);
// 	printf("dst: %s\n", dst);
// 	printf("returned length: %zu\n", result);
// 	printf("actual dst length: %zu\n\n", strlen(dst));

// 	// テストケース2: バッファサイズが小さい場合
// 	result = ft_strlcpy(dst, src, 7);
// 	printf("Test2 - Small Buffer (size=7):\n");
// 	printf("src: %s\n", src);
// 	printf("dst: %s\n", dst);
// 	printf("returned length: %zu\n", result);
// 	printf("actual dst length: %zu\n\n", strlen(dst));

// 	// テストケース3: サイズ0でのコピー
// 	result = ft_strlcpy(dst, src, 0);
// 	printf("Test3 - Zero Size:\n");
// 	printf("src: %s\n", src);
// 	printf("returned length: %zu\n\n", result);

// 	// テストケース4: 空文字列のコピー
// 	char empty[] = "";
// 	result = ft_strlcpy(dst, empty, sizeof(dst));
// 	printf("Test4 - Empty String:\n");
// 	printf("src: (empty string)\n");
// 	printf("dst: %s\n", dst);
// 	printf("returned length: %zu\n", result);
// 	printf("actual dst length: %zu\n", strlen(dst));

// 	return (0);
// }