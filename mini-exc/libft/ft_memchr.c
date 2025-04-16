/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 15:51:42 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:08:39 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			byte;
	unsigned char	*str;

	str = (unsigned char *)s;
	byte = 0;
	while (byte < n)
	{
		if (str[byte] == (unsigned char)c)
		{
			return (&str[byte]);
		}
		byte++;
	}
	return (0);
}
