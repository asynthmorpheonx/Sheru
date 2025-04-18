/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 12:13:54 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:59 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buff;
	size_t	i;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		return (ft_strdup(""));
	}
	if (len > slen - start)
		len = slen - start;
	buff = (char *) malloc(len + 1);
	if (buff == NULL)
		return (NULL);
	i = 0;
	while ((s[start] != '\0') && i < len)
	{
		buff[i] = s[start];
		start++;
		i++;
	}
	buff[i] = '\0';
	return (buff);
}
