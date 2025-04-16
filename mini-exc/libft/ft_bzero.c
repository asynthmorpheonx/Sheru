/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:54:30 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:12 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			byte;
	unsigned char	*str;

	str = s;
	byte = 0;
	while (n--)
	{
		str[byte++] = 0;
	}
}
/*
int main()
{
	char str[] = "1111111111";
	bzero(str, 5);
	printf("bzero did this%s\n", str);
	char st[] =  "1111111111";
	ft_bzero(st, 5);
	printf("ft_bzero did this%s\n", st);
}*/
