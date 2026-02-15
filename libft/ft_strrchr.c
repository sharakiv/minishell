/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharaki <sharaki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:59:06 by sharaki           #+#    #+#             */
/*   Updated: 2024/11/08 03:13:25 by sharaki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = s;
	while (*last != '\0')
		last++;
	while (last >= s)
	{
		if (*last == (char)c)
			return ((char *)last);
		last--;
	}
	return (NULL);
}
