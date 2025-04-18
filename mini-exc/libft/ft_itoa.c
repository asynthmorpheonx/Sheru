/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 11:41:38 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:56 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_static_fill(char *buff, int n, int u)
{
	while (n)
	{
		buff[u] = (n % 10) + 48;
		n = n / 10;
		u--;
	}
	return (buff);
}

static char	*ft_static_zero(int n)
{
	char	*str;

	str = malloc(2);
	if (!str)
		return (NULL);
	str[0] = n + 48;
	str[1] = '\0';
	return (str);
}

static int	ft_static_count(int n)
{
	int	count;

	count = 0;
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				u;

	if (n == 0)
		return (ft_static_zero(n));
	else if (n != 0)
	{
		if (n == -2147483648)
			return (ft_strdup("-2147483648"));
		u = 0;
		if (n < 0)
			u++;
		u += ft_static_count(n);
		str = malloc(u + 1);
		if (str == NULL)
			return (NULL);
		if (n < 0)
		{
			str[0] = '-';
			n = -n;
		}
		str[u] = '\0';
		return (ft_static_fill(str, (unsigned int)n, --u));
	}
	return (NULL);
}
