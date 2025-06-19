/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:39:38 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/19 16:13:44 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static bool	odup(t_file *ptr)
{
	int	i;
	int	fd;

	i = 0;
	while (ptr->outfile[i])
	{
		if (ptr->o_type[i] == APP || ptr->o_type[i] == OUD)
		{
			if (ptr->o_type[i] == OUD)
				fd = open(ptr->outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(ptr->outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
				return (err(ptr->outfile[i], 3, 0), 0);
			dup2(fd, 1);
			close(fd);
		}
		else if (ptr->o_type[i] == -1)
			return (err(ptr->outfile[i], 4, 0), 0);
		i++;
	}
	return (true);
}

static bool	idup(t_file *ptr)
{
	int	i;
	int	fd;

	i = 0;
	while (ptr->infile[i])
	{
		if (ptr->i_type[i] == IND)
		{
			fd = open(ptr->infile[i], O_RDONLY);
			if (fd == -1)
				return (err(ptr->infile[i], 3, 0), 0);
			dup2(fd, 0);
			close(fd);
		}
		else if (ptr->i_type[i] == HERDOC && !ptr->infile[i + 1])
		{
			fd = ft_atoi(ptr->infile[i]);
			dup2(fd, 0);
			close(fd);
		}
		else if (ptr->i_type[i] == -1)
			return (err(ptr->infile[i], 4, 0), 0);
		i++;
	}
	return (true);
}

bool	redirect(t_data *cmd)
{
	if (cmd->file.infile && !idup(&cmd->file))
		return (false);
	if (cmd->file.outfile && !odup(&cmd->file))
		return (false);
	return (true);
}
