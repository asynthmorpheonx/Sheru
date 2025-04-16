/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:28:49 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:09:55 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				index;
	unsigned char	o;

	o = (unsigned char)c;
	index = 0;
	while (s[index])
	{
		if (s[index] == o)
		{
			return ((char *)&s[index]);
		}
		index++;
	}
	if (!o)
		return ((char *)&s[index]);
	else
		return (0);
}
