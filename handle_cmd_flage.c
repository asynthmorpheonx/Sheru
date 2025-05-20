/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_flage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/07 16:18:55 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	cmd_count(char **strs, int *arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == IND || arr[i] == OUD
			|| arr[i] == APP || arr[i] == HERDOC)
			i++;
		else
			j++;
		i++;
	}
	return (j);
}

void	cmd_filler(char **strs, int *arr, char **buffer)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == IND || arr[i] == OUD 
			|| arr[i] == APP || arr[i] == HERDOC)
			i++;
		else
			buffer[j++] = strs[i];
		i++;
	}
}

void	cmd_flag_handle(char **strs, int *arr, t_data *node, int *mode)
{
	int	j;

	j = cmd_count(strs, arr);
	node->cmd = safe_alloc((j + 1) * sizeof(char *), 0);
	if (!node->cmd)
		exit (EXIT_FAILURE);
	cmd_filler(strs, arr, node->cmd);
	*mode = 0;
}
