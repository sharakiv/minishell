/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:38:27 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 06:24:37 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*actual_len;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (!f)
		return (NULL);
	len = ft_strlen(s);
	actual_len = malloc(sizeof(char) * (len + 1));
	if (actual_len == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		actual_len[i] = f(i, s[i]);
		i++;
	}
	actual_len[i] = '\0';
	return (actual_len);
}

// char	to_upper(unsigned int i, char c)
// {
// 	return ((c >= 'a' && c <= 'z') ? c - 32 : c);
// }

// int	main(void)
// {
// 	// 基本的なテスト
// 	char *result1 = ft_strmapi("hello", to_upper);
// 	printf("Test1 (hello): %s\n", result1);
// 	free(result1);

// 	// 空文字列のテスト
// 	char *result2 = ft_strmapi("", to_upper);
// 	printf("Test2 (empty string): %s\n", result2);
// 	free(result2);

// 	// NULLポインタのテスト
// 	char *result3 = ft_strmapi(NULL, to_upper);
// 	printf("Test3 (NULL string): %s\n", result3);
// 	free(result3);

// 	return (0);
// }