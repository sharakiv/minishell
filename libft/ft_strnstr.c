/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 00:55:12 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:13:08 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	if (little[0] == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	if (!len)
		return (NULL);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while ((i + j) < len && big[i + j] && big[i + j] == little[j])
		{
			j++;
		}
		if (j == little_len)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
