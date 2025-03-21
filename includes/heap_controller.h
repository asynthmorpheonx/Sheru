/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_controller.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:47:07 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/21 03:48:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAP_CONTROLLER_H
# define HEAP_CONTROLLER_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_container
{
	void				*content;
	struct s_container	*next;
}	t_container;

void		g_lst_clear(t_container **lst, void (*del)(void*));
void		g_lst_addback(t_container *new);
void		g_lst_delone(t_container *lst, void (*del)(void*));
t_container	*g_new_garbage(void *content);
void		delete_one(void *data_ref);
void		fill_zero(void *s, size_t len);
void		*safe_alloc(size_t byts_count, int mode);
t_container	**container(void);
void		clear_container(void);
void		print_stack(void);

#endif