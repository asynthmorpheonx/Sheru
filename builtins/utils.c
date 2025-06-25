/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 00:00:08 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/25 21:42:02 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_offs	*offs(void)
{
	static t_offs	x;

	return (&x);
}

void	sort_tenv(char **env)
{
	char	*tmp;
	int		i;
	int		u;

	i = 0;
	while (env[i])
	{
		u = i + 1;
		while (env[u])
		{
			if (ft_strcmp(env[u], env[i]) < 0)
			{
				tmp = env[u];
				env[u] = env[i];
				env[i] = tmp;
			}
			u++;
		}
		i++;
	}
}

void	dfl_path_err(void)
{
	if (!offs()->dfl_pth)
		ft_putendl_fd(": command not found", 2);
	else
		ft_putendl_fd(": No such file or directory", 2);
}

void	err(char *str, int error_status, bool ex_it)
{
	if (error_status == 4)
		ft_putendl_fd("sheru: ", 2);
	if (error_status != 3)
		ft_putstr_fd(str, 2);
	if (error_status == 1)
		ft_putendl_fd(": command not found", 2);
	else if (error_status == 2)
		ft_putendl_fd(": Permission denied", 2);
	else if (error_status == 3)
		perror(str);
	else if (error_status == 4)
		ft_putendl_fd(": ambiguous redirect", 2);
	else if (error_status == 127)
		dfl_path_err();
	else if (error_status == 126)
		ft_putendl_fd(": permission denied", 2);
	else if (error_status == 5)
		ft_putendl_fd(": No such file or directory", 2);
	else if (error_status == 6)
		ft_putendl_fd(": Is a directory", 2);
	else if (error_status == 7)
		return (ft_putendl_fd(": numeric argument required", 2));
	clear_container();
	if (ex_it)
		exit(EXIT_FAILURE);
}
