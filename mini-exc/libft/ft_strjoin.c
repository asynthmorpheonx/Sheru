/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:48:41 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:15 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_static_add(const char *str, char *buff, int *b)
{
	int	i;

	i = 0;
	while (str[i])
	{
		buff[*b] = str[i];
		i++;
		(*b)++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buff;
	int		total_len;
	int		i;
	int		b;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	buff = (char *) malloc(total_len + 1);
	if (buff == NULL)
		return (NULL);
	b = 0;
	i = 0;
	ft_static_add(s1, buff, &b);
	ft_static_add(s2, buff, &b);
	buff[b] = '\0';
	return (buff);
}
