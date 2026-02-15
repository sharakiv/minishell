/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 10:39:35 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:22:28 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			total_size;
	void			*ptr;
	unsigned char	*p;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total_size = nmemb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	p = ptr;
	while (total_size--)
		*p++ = 0;
	return (ptr);
}
// int	main(void)
// {
// 	// テストケース1: 通常の確保
// 	int *arr1 = ft_calloc(5, sizeof(int));
// 	if (arr1)
// 	{
// 		printf("Test1: Allocated 5 ints:\n");
// 		for (int i = 0; i < 5; i++)
// 			printf("%d ", arr1[i]); // すべて0が出力されるはず
// 		printf("\n");
// 		free(arr1);
// 	}

// 	// テストケース2: サイズ0
// 	int *arr2 = ft_calloc(0, sizeof(int));
// 	printf("Test2: Zero size allocation: %p\n", (void *)arr2);
// 	free(arr2);

// 	// テストケース3: オーバーフローチェック
// 	void *arr3 = ft_calloc(SIZE_MAX, 2);
// 	printf("Test3: Overflow check: %p\n", arr3); // NULLが返されるはず

// 	return (0);
// }