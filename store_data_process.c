/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:16:29 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/07 16:17:16 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_data	*last_node(t_data *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	store_in_tdata(t_data **node, t_data *tmp)
{
	if (!*node)
		*node = tmp;
	else
		last_node(*node)->next = tmp;
}

// it store the char **strs in linked-list.
bool	stor_in_list(char **strs, int *arr, t_data **node)
{
	int		i;
	int		to;
	int		bo;
	int		zo;
	t_data	*tmp;

	i = 0;
	while (strs[i])
	{
		to = 1;
		bo = 1;
		zo = 1;
		tmp = safe_alloc(sizeof(t_data), 0);
		if (!tmp)
			return (false);
		if (arr[i] == PIPE)
			i++;
		while (strs[i] && arr[i] != PIPE)
		{
			if (arr[i] == WORD)
			{
				if (to)
					cmd_flag_handle(strs + i, arr + i, tmp, &to);
				i++;
				continue;
			}
			else if ((arr[i] == APP || arr[i] == OUD || arr[i] == IND) && bo)
				handle_redirections(arr + i, strs + i, &tmp->file, &bo);
			else if (arr[i] == HERDOC && zo)
				tmp->her_doc = heredoc_heandler(strs + i, arr + i, &zo);
			i += 2;
		}
		store_in_tdata(node, tmp);
	}
	return (true);
}
