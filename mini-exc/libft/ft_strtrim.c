/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 15:32:50 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:55 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_last(const char *str, const char *set, int *index)
{
	int (i), (u), (matched), (p);
	p = 0;
	u = ft_strlen(str) - 1;
	while (str[u])
	{
		i = 0;
		matched = 0;
		while (set[i])
		{
			if (set[i] == str[u])
			{
				matched = 1;
				p++;
				break ;
			}
			i++;
		}
		if (!matched)
			break ;
		u--;
	}
	*index = u;
	return (p);
}

static size_t	ft_first(const char *str, const char *set, int *i)
{
	int (u), (o), (matched), (p);
	o = 0;
	p = 0;
	while (str[o])
	{
		u = 0;
		matched = 0;
		while (set[u])
		{
			if (set[u] == str[o])
			{
				matched = 1;
				p++;
				break ;
			}
			u++;
		}
		if (!matched)
			break ;
		o++;
	}
	*i = o;
	return (p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*buff;
	int			i;
	int			first;
	int			last;
	size_t		size;

	if (!s1 || !set)
		return (NULL);
	size = ft_first(s1, set, &first) + ft_last(s1, set, &last);
	if (ft_strlen(s1) <= size)
		return (ft_strdup(""));
	buff = (char *)malloc(ft_strlen(s1) - size + 1);
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (first <= last)
	{
		buff[i] = s1[first];
		i++;
		first++;
	}
	buff[i] = '\0';
	return (buff);
}
