/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:39:34 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

static void	echo_print(char **str)
{
	int	i;

	i = 0;
	if (write(1, NULL, 0) == -1)
		return (perror("sheru: echo: write error"), code_setter(1));
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
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

int	check_flags(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		if (arg[i][0] != '-')
			return (i);
		j = 1;
		while (arg[i][j])
		{
			if (arg[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

void	ft_echo(t_data *cmd)
{
	bool	mode;
	int		i;

	mode = false;
	i = 2;
	code_setter(0);
	if (cmd->cmd[1])
		mode = check_n(cmd->cmd[1]);
	if (mode)
	{
		i += check_flags(cmd->cmd + 2);
		echo_print(cmd->cmd + i);
	}
	else
	{
		echo_print(cmd->cmd + 1);
		printf("\n");
	}
}
