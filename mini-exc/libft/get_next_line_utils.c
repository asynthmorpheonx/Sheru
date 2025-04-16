/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:36:36 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/03/17 02:47:37 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_getn(t_list *lst)
{
	int	i;

	if (lst == NULL)
		return (0);
	while (lst)
	{
		i = 0;
		while (((char *)lst->content)[i])
		{
			if (((char *)lst->content)[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*lastnode(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
	}
	return (lst);
}

int	lenton(t_list *lst)
{
	int	len;
	int	i;

	len = 0;
	while (lst)
	{
		i = 0;
		while (((char *)lst->content)[i])
		{
			if (((char *)lst->content)[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		lst = lst->next;
	}
	return (len);
}

void	copy_str(t_list *lst, char *buf)
{
	int	i;
	int	u;

	u = 0;
	while (lst)
	{
		i = 0;
		while (((char *)lst->content)[i])
		{
			if (((char *)lst->content)[i] == '\n')
			{
				buf[u++] = '\n';
				buf[u] = '\0';
				return ;
			}
			buf[u++] = ((char *)lst->content)[i++];
		}
		lst = lst->next;
	}
	buf[u] = '\0';
}

void	ft_free_gnl(t_list **lst, char *buf, t_list *node)
{
	t_list	*temp;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	if (node != NULL && node->content != NULL && ((char *)node->content)[0] != '\0')
	{
		*lst = node;
	}
	else
	{
		free(buf);
		free(node);
	}
}
