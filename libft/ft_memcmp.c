/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 19:09:44 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:17:11 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*sp1;
	const unsigned char	*sp2;
	size_t				i;

	i = 0;
	sp1 = (const unsigned char *)s1;
	sp2 = (const unsigned char *)s2;
	while (n > i)
	{
		if (sp1[i] != sp2[i])
			return (sp1[i] - sp2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	str1[] = "Hello,World!";
// 	char	str2[] = "Hellp,World!";
// 	int		c_result;
// 	int		ft_result;

// 	c_result = memcmp(str1, str2, 5);
// 	ft_result = ft_memcmp(str1, str2, 5);
// 	printf("c_result = %d\nft_result = %d\n", c_result, ft_result);
// 	return (0);
// }
