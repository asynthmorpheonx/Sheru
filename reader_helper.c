/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:32:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

void	replace_fd(t_data *node, char *str, int i)
{
	if (str)
	{
		delete_one(node->file.infile[i]);
		node->file.infile[i] = str;
		g_lst_addback(g_new_garbage(str));
	}
}

void	here_doc_util(char *input, int fd)
{
	if (util()->herdoc_exp)
		expand_herdoc_data(input, fd);
	else if (*input)
		write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

void	safe_pipe(int *fds)
{
	if (pipe(fds) == -1)
	{
		perror("pipe");
		ult_exit();
	}
}

void	close_herdoc_ports(void)
{
	int	i;

	i = 0;
	while (util()->ports[i] != 0)
	{
		close(util()->ports[i]);
		i++;
	}
}
