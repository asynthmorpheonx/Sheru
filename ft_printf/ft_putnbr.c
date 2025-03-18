/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:09:59 by mel-mouh          #+#    #+#             */
/*   Updated: 2024/11/20 12:21:48 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	leen(int n)
{
	int				i;
	unsigned int	m;

	i = 0;
	if (n < 0)
	{
		m = -n;
		i++;
	}
	else
		m = n;
	while (m > 0)
	{
		m /= 10;
		i++;
	}
	return (i);
}

int	ft_putnbr(int n)
{
	unsigned int	m;
	int				i;

	if (n < 0)
	{
		ft_putchar('-');
		m = -n;
	}
	else if (n == 0)
		return (write(1, "0", 1));
	else
		m = n;
	i = leen(n);
	if (m > 9)
	{
		ft_putnbr(m / 10);
		ft_putchar((m % 10) + '0');
	}
	else
		ft_putchar(m + '0');
	return (i);
}
