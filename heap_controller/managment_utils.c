/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   managment_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:44:40 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/21 03:47:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap_controller.h"

void	g_lst_clear(t_container **lst, void (*del)(void*))
{
	t_container	*curr_node;
	t_container	*next_node;

	curr_node = *lst;
	while (curr_node)
	{
		next_node = curr_node->next;
		if (curr_node->content)
			(del)(curr_node->content);
		free(curr_node);
		curr_node = next_node;
	}
	*lst = NULL;
}

void	g_lst_addback(t_container *new)
{
	t_container	*last;
	t_container	**lst;

	lst = container();
	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (last->next)
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

void	print_stack(void)
{
	t_container	*node;

	node = *container();
	while (node)
	{
		printf("=============%s=============\n",
			(char *)node->content);
		node = node->next;
	}
	printf("%s", (char *)node);
}
