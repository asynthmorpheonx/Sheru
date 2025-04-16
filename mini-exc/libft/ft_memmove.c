/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:00:13 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:08:55 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		index;
	const unsigned char	*from;
	unsigned char		*to;

	from = (const unsigned char *)src;
	to = (unsigned char *)dst;
	if (dst > src)
	{
		while (len--)
		{
			to[len] = from[len];
		}
	}
	else if (src > dst)
	{
		index = 0;
		while (index < len)
		{
			to[index] = from[index];
			index++;
		}
	}
	return (dst);
}
