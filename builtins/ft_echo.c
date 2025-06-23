/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:39:34 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:49:57 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	echo_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		if (str[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
}

static bool	check_n(char *arg)
{
	int	i;

	if (*arg != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	if (i == 1 && !arg[i])
		return (false);
	return (true);
}

void	ft_echo(t_data *cmd)
{
	bool	mode;

	mode = false;
	if (cmd->cmd[1])
		mode = check_n(cmd->cmd[1]);
	if (mode)
	{
		echo_print(cmd->cmd + 2);
	}
	else
	{
		echo_print(cmd->cmd + 1);
		printf("\n");
	}
}
