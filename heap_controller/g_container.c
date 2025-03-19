/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_container.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 06:41:41 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/19 02:02:14 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heap_controller.h"

t_container	**container(void)
{
	static t_container	*pp;

	return (&pp);
}

void	clear_container(void)
{
	g_lst_clear(container(), free);
}

void	delete_one(void *data_ref)
{
	t_container	*prev;
	t_container	*lst;
	t_container	**head;

	prev = NULL;
	head = container();
	lst = *head;
	while (lst)
	{
		if (data_ref == lst->content)
		{
			if (prev)
				prev->next = lst->next;
			else
				*head = lst->next;
			g_lst_delone(lst, free);
			return ;
		}
		prev = lst;
		lst = lst->next;
	}
}

void	*safe_alloc(size_t byts_count, int mode)
{
	void		*array;
	t_container	*new_node;

	array = malloc(byts_count);
	if (!array)
	{
		clear_container();
		return (perror(""), NULL);
	}
	new_node = g_new_garbage(array);
	if (!new_node)
	{
		free(array);
		clear_container();
		return (perror("malloc"), NULL);
	}
	g_lst_addback(container(), new_node);
	if (!mode)
		fill_zero(array, byts_count);
	return (array);
}

void	fill_zero(void *s, size_t len)
{
	unsigned char	*str;
	size_t			i;

	if (!s)
		return ;
	str = (unsigned char *)s;
	i = 0;
	while (i < len)
		str[i++] = 0;
}
