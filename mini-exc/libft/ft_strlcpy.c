/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:00:36 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:24 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	index;
	size_t	u;

	index = 0;
	while (src[index])
	{
		index++;
	}
	if ((index == 0) && (dstsize == 0))
		return (0);
	if (dstsize > 0)
	{
		u = 0;
		while (src[u] && u < dstsize - 1)
		{
			dest[u] = src[u];
			u++;
		}
		dest[u] = '\0';
	}
	return (index);
}
