/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 23:07:50 by mel-mouh          #+#    #+#             */
/*   Updated: 2024/11/20 12:20:52 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	conversions(char spiecifier, va_list args)
{
	int	count;

	count = 0;
	if (spiecifier == 'c')
		count += ft_putchar((char)va_arg(args, int));
	else if (spiecifier == 'd' || spiecifier == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (spiecifier == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (spiecifier == 'x')
		count += ft_putnbr_hex(va_arg(args, unsigned), "0123456789abcdef");
	else if (spiecifier == 'X')
		count += ft_putnbr_hex(va_arg(args, unsigned), "0123456789ABCDEF");
	else if (spiecifier == 'p')
		count += ft_putaddres((unsigned long int)va_arg(args, void *));
	else if (spiecifier == 'u')
		count += ft_putunsigned(va_arg(args, unsigned));
	else if (spiecifier == '%')
		count += ft_putchar('%');
	else
		return (-1);
	return (count);
}
