/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 16:34:55 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/02/27 21:07:41 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
/*
int main()
{
	char str[] = "abc123   &%'";
	int i = ft_isprint((unsigned char*)str);
	if(i == 0)
		printf("noo! \n");
	else if(i == 1)
		printf("yiss! \n");
	return (0);
}*/
