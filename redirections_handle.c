/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_handle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:07:45 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

void	stor_redirections(int *arr, char **strs, t_file *file, int i)
{
	int (j), (p);
	j = 0;
	p = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == APP || arr[i] == OUD)
		{
			file->outfile[j++] = strs[i + 1];
			file->o_type[j - 1] = arr[i];
			if (arr[i + 1] == -1)
				file->o_type[j - 1] = -1;
			i += 2;
		}
		else if (arr[i] == IND || arr[i] == HERDOC)
		{
			file->infile[p++] = strs[i + 1];
			file->i_type[p - 1] = arr[i];
			if (arr[i + 1] == -1)
				file->i_type[p - 1] = -1;
			i += 2;
		}
		else
			i++;
	}
}

void	make_a_file(int incount, int outcount, t_file *file)
{
	file->infile = safe_alloc((incount + 1) * sizeof(char *), 0);
	file->outfile = safe_alloc((outcount + 1) * sizeof(char *), 0);
	file->o_type = safe_alloc(outcount * sizeof(int), 0);
	file->i_type = safe_alloc(incount * sizeof(int), 0);
	if (!file->o_type || !file->outfile || !file->infile || !file->i_type)
		exit(EXIT_FAILURE);
}

void	count_in_out(int *in, int *out, int *arr, char **strs)
{
	int	i;
	int	herdoc;

	i = 0;
	herdoc = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] < PIPE || arr[i] == HERDOC)
		{
			if (arr[i] == IND || arr[i] == HERDOC)
			{
				if (arr[i] == HERDOC)
					herdoc++;
				(*in)++;
			}
			else
				(*out)++;
			i += 2;
		}
		else
			i++;
	}
	if (herdoc > 16)
		exit (2);
}

void	handle_redirections(int *arr, char **strs, t_file *file, int *mode)
{
	int	incount;
	int	outcount;

	incount = 0;
	outcount = 0;
	count_in_out(&incount, &outcount, arr, strs);
	make_a_file(incount, outcount, file);
	stor_redirections(arr, strs, file, 0);
	*mode = 0;
}
