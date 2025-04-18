/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:59:53 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:08:51 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				index;
	const unsigned char	*from;
	unsigned char		*to;

	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	if (n == 0)
		return (dst);
	from = (const unsigned char *)src;
	to = (unsigned char *)dst;
	index = 0;
	while (index < n)
	{
		to[index] = from[index];
		index++;
	}
	return (dst);
}
