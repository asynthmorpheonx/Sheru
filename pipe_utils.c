/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:24:00 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 22:31:14 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void make_pipe(void)
{
	if (pipe(offs()->fpi) == -1 || pipe(offs()->spi) == -1)
	{
		if (offs()->pids)
			free(offs()->pids);
		close_pipes();
		err("pipe", 3, 1);
	}
}

void	pipe_indexing(void)
{
	if (executer()->ind % 2 == 0)
	{
		close(offs()->fpi[0]);
		close(offs()->fpi[1]);
		if (pipe(offs()->fpi) == -1)
		{
			if (offs()->pids)
				free(offs()->pids);
			err("pipe", 3, 1);
		}
	}
	else
	{
		close(offs()->spi[0]);
		close(offs()->spi[1]);
		pipe(offs()->spi);
		if (pipe(offs()->spi) == -1)
		{
			if (offs()->pids)
				free(offs()->pids);
			err("pipe", 3, 1);
		}
	}		
}
