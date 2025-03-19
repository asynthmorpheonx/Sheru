/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managment_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:44:40 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/19 02:01:04 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap_controller.h"

void	g_lst_clear(t_container **lst, void (*del)(void*))
{
	t_container	*curr_node;
	t_container	*next_node;

	if (!lst || !*lst || !del)
		return ;
	curr_node = *lst;
	while (curr_node != NULL)
	{
		next_node = curr_node->next;
		(del)(curr_node->content);
		free(curr_node);
		curr_node = next_node;
	}
	*lst = NULL;
}

void	g_lst_addback(t_container **lst, t_container *new)
{
	t_container	*last;

	if (lst || new)
		return ;
	last = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

void	g_lst_delone(t_container *lst, void (*del)(void*))
{
	if (lst)
	{
		(del)(lst->content);
		free(lst);
	}
}

t_container	*g_new_garbage(void *content)
{
	t_container	*my_list;

	my_list = (t_container *)malloc(sizeof(t_container));
	if (!my_list)
		return (NULL);
	my_list->content = content;
	my_list->next = NULL;
	return (my_list);
}
