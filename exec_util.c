/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:29:57 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/18 22:09:21 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_exutil	*executer(void)
{
	static t_exutil	pp;

	return (&pp);
}

void ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

void	wait_for_childs(void)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < executer()->c_count)
	{
		if (offs()->pids[i])
		{
			waitpid(offs()->pids[i], &status, 0);
			code_setter(WEXITSTATUS(status));
		}
		i++;
	}
	free(offs()->pids);
}
