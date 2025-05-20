/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:libft/ft_strcmp.c
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:14:00 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/05/02 12:42:47 by hoel-mos         ###   ########.fr       */
=======
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 20:17:37 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/05/19 17:44:38 by mel-mouh         ###   ########.fr       */
>>>>>>> main:mini-exc/libft/ft_strncmp.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcmp(char *s1, const char *s2)
{
	int i;

	i = 0;
	while ((s1[i] != '\0') && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}