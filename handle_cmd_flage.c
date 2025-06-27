/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd_flage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:18:25 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

int	cmd_count(char **strs, int *arr, int i)
{
	int	j;

	j = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == IND || arr[i] == OUD
			|| arr[i] == APP || arr[i] == HERDOC)
			i++;
		else if (*strs[i] || (!*strs[i] && !*util()->mask[i]))
			j++;
		i++;
	}
	return (j);
}

void	cmd_filler(char **strs, int *arr, char **buffer, int i)
{
	int	j;

	j = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == IND || arr[i] == OUD
			|| arr[i] == APP || arr[i] == HERDOC)
			i++;
		else if (*strs[i] || (!*strs[i] && !*util()->mask[i]))
			buffer[j++] = strs[i];
		i++;
	}
}

void	cmd_flag_handle(char **strs, int *arr, t_data *node, int i)
{
	int	j;

	j = cmd_count(strs, arr, i);
	node->cmd = safe_alloc((j + 1) * sizeof(char *), 0);
	if (!node->cmd)
		exit (EXIT_FAILURE);
	cmd_filler(strs, arr, node->cmd, i);
}
