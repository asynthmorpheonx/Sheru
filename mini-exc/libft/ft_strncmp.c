/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:17:37 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:10:41 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	if (n == 0)
		return (0);
	index = 0;
	while (index < n && (s1[index] || s2[index]))
	{
		if ((unsigned char)s1[index] != (unsigned char)s2[index])
			return ((unsigned char)s1[index] - (unsigned char)s2[index]);
		index++;
	}
	return (0);
}
