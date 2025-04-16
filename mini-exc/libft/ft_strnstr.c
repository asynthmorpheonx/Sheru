/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:59:58 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:45 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_static_checkstr(const char *str, const char *find)
{
	int	index;

	index = 0;
	while (find[index] != '\0')
	{
		if (str[index] != find[index])
		{
			return (0);
		}
		index++;
	}
	return (1);
}

char	*ft_strnstr(const char *string, const char *to_find, size_t len)
{
	size_t	index;
	size_t	find;
	size_t	needle;

	needle = ft_strlen(to_find);
	if (to_find[0] == '\0')
		return ((char *)string);
	index = 0;
	while (string[index] && len > 0)
	{
		if (len < needle)
			return (NULL);
		find = 0;
		if (string[index] == to_find[find])
		{
			if (ft_static_checkstr(&string[index], to_find))
			{
				return ((char *)&string[index]);
			}
		}
		index++;
		len--;
	}
	return (NULL);
}
