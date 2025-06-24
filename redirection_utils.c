/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:39:38 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/24 02:28:28 by mel-mouh         ###   ########.fr       */
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

static bool	p_odup(t_file *ptr)
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
				return (redir_msg_err(1, ptr->outfile[i]), 0);
			dup2(fd, 1);
			close(fd);
		}
		else if (ptr->o_type[i] == -1)
			return (redir_msg_err(2, ptr->outfile[i]), 0);
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

static bool	p_idup(t_file *ptr)
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
				return (redir_msg_err(1, ptr->infile[i]), 0);
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
			return (redir_msg_err(2, ptr->infile[i]), 0);
		i++;
	}
	return (true);
}

bool	redirect(t_data *cmd, bool child_pr)
{
	if (child_pr)
	{
		if (cmd->file.infile && !idup(&cmd->file))
			return (false);
		if (cmd->file.outfile && !odup(&cmd->file))
			return (false);
	}
	else
	{
		if (cmd->file.infile && !p_idup(&cmd->file))
		{
			code_setter(1);
			return (false);
		}
		if (cmd->file.outfile && !p_odup(&cmd->file))
		{
			code_setter(1);
			return (false);
		}
	}
	return (true);
}
