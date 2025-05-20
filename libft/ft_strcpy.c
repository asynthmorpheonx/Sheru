/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:10:00 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:29:56 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dest, const char *src)
{
	size_t	u;

	if (!src || !*src)
		return (0);
	u = 0;
	while (src[u])
	{
		dest[u] = src[u];
		u++;
	}
	return (dest);
}