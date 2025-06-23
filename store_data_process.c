/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:16:29 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 22:46:20 by mel-mouh         ###   ########.fr       */
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

void	store_word_nd_redirs(int *i, t_data	*tmp, int *to, int *bo)
{
	if (util()->a[*i] == WORD)
	{
		if (*to && (*to)--)
			cmd_flag_handle(util()->s, util()->a, tmp, *i);
		(*i)++;
	}
	else if (util()->a[*i] < PIPE || util()->a[*i] == HERDOC)
	{
		if (*bo)
			handle_redirections(util()->a + *i, util()->s + *i, &tmp->file, bo);
		(*i) += 2;
	}
}

bool	stor_in_list(char **strs, int *arr, t_data **node)
{
	int		i;
	int		to;
	int		bo;
	t_data	*tmp;

	i = 0;
	while (strs[i])
	{
		to = 1;
		bo = 1;
		tmp = safe_alloc(sizeof(t_data), 0);
		if (!tmp)
			return (false);
		if (arr[i] == PIPE)
			i++;
		while (strs[i] && arr[i] != PIPE)
			store_word_nd_redirs(&i, tmp, &to, &bo);
		store_in_tdata(node, tmp);
	}
	return (true);
}
