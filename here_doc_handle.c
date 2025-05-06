/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 21:55:42 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/06 21:59:02 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	here_doc_count(int *arr, char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == HERDOC)
		{
			j++;
			i += 2;
		}
		else
			i++;
	}
	if (!j || j > 16)
	{
		if (j)
		{
			ft_putstr_fd("maximum here-document", 2);
			ft_putendl_fd(" count exceeded", 2);
		}
		return (0);
	}
	return (j);
}

char	**stor_delimiters(int *arr, char **str, int count)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = 0;
	buff = safe_alloc((count + 1) * sizeof(char *), 0);
	if (!buff)
		return (NULL);
	while (str[i] && arr[i] != PIPE)
	{
		if (arr[i] == HERDOC)
		{
			buff[j++] = str[i + 1];
			i += 2;
		}
		else
			i++;
	}
	return (buff);
}

char	**heredoc_heandler(char **str, int *arr, int *mode)
{
	int		j;

	j = here_doc_count(arr, str);
	if (!j)
		return (NULL);
	*mode = 0;
	return (stor_delimiters(arr, str, j));
}
