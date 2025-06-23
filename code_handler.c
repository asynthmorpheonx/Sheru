/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:22:00 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:20:08 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

char	*exit_code(void)
{
	static char	exit_status[4];

	return (exit_status);
}

void	code_setter(int new_code)
{
	int	i;

	i = 0;
	new_code = (new_code % 256 + 256) % 256;
	if (new_code < 9)
		i = 0;
	else if (new_code < 99)
		i = 1;
	else
		i = 2;
	exit_code()[i + 1] = '\0';
	if (!new_code)
		exit_code()[0] = 48;
	else
	{
		while (new_code)
		{
			exit_code()[i] = new_code % 10 + '0';
			i--;
			new_code /= 10;
		}
	}
}
