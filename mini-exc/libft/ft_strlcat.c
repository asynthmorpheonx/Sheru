/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:40:46 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:20 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dsize)
{
	size_t	index;
	size_t	slen;
	size_t	dlen;
	size_t	lenresult;

	dlen = 0;
	slen = 0;
	slen = ft_strlen(src);
	if (dest != NULL && dsize != 0)
		dlen = ft_strlen(dest);
	if (dsize <= dlen)
		lenresult = (dsize + slen);
	if (dsize > dlen)
		lenresult = (dlen + slen);
	if (dsize > 0)
	{
		index = 0;
		while ((src[index] != '\0') && dlen + index < dsize - 1)
		{
			dest[dlen + index] = src[index];
			index++;
		}
		dest[dlen + index] = '\0';
	}
	return (lenresult);
}
