/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:25:11 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/22 23:33:45 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	expand_herdoc_data(char *str, int fd)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			tmp = key_value(str + i + 1);
			len = key_len(str + i, 0);
			if (str[i + 1] == '?')
				len++;
			if (*tmp)
				write(fd, tmp, ft_strlen(tmp));
			i += len;
		}
		else
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

void	replace_fd(t_data *node, char *str, int i)
{
	delete_one(node->file.infile[i]);
	node->file.infile[i] = str;
	g_lst_addback(g_new_garbage(str));
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

char	*here_doc_reader(char *str, bool mode, int i)
{
	char	*input;
	int		fds[2];

	input = NULL;
	if (mode)
		safe_pipe(fds);
	*process_status() = HERDOC_READ;
	while (1)
	{
		input = readline("> ");
		if (*process_status() == INTERRUPTED
			|| !input || !ft_memcmp(input, str, ft_strlen(input) + 1))
			break;
		if (mode)
			here_doc_util(input, fds[1]);
		free(input);
		input = NULL;
	}
	if (mode)
		close(fds[1]);
	if (mode)
	{
		util()->ports[i] = fds[0];
		return (ft_itoa(fds[0]));
	}
	return (NULL);
}

void	herdoc_job(void)
{
	int		i;
	char	*str;
	t_data	*tmp;
	int		ind;

	i = 0;
	ind = 0;
	tmp = *box();
	while (tmp)
	{
		while (tmp->file.infile && tmp->file.infile[i])
		{
			if (tmp->file.i_type[i] == HERDOC && tmp->file.infile[i + 1])
				here_doc_reader(tmp->file.infile[i], false, ind);
			else if (tmp->file.i_type[i] == HERDOC)
			{
				str = here_doc_reader(tmp->file.infile[i], true, ind);
				if (str)
					replace_fd(tmp, str, i);
				ind++;
			}
			if (*process_status() == INTERRUPTED)
				return (close_herdoc_ports());
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
}
