/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 12:25:41 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:50 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				index;
	unsigned char	o;

	o = (unsigned char)c;
	index = ft_strlen(s);
	if (o == '\0')
	{
		return ((char *)&s[index]);
	}
	while (index >= 0)
	{
		if (s[index] == o)
		{
			return ((char *)&s[index]);
		}
		index--;
	}
	return (0);
}
