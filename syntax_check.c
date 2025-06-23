/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:26:43 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:45:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	syntax_err_msg(char *err)
{
	ft_putstr_fd("sheu: syntax error near unexpected token `", 2);
	if (err)
		ft_putstr_fd(err, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
	code_setter(2);
}

bool	syntax_check(void)
{
	int	i;

	i = 0;
	while (i < util()->t)
	{
		if (util()->a[i] == PIPE
			&& (i + 1 >= util()->t || !i || util()->a[i - 1] != WORD))
			return (syntax_err_msg(util()->s[i + 1]), false);
		else if ((util()->a[i] == IND || util()->a[i] == OUD)
			&& (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (syntax_err_msg(util()->s[i + 1]), false);
		else if ((util()->a[i] == APP || util()->a[i] == HERDOC)
			&& (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (syntax_err_msg(util()->s[i + 1]), false);
		i++;
	}
	return (true);
}
