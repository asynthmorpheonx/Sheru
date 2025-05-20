/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_nd_store_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:00 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/06 22:01:37 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

// it returns pointer the last node in the list "lst".
t_envp	*last_env(t_envp *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// it just adds the node *tmp to the linked list **lst.
void	add_to_envp(t_envp **lst, t_envp *tmp)
{
	if (!*lst)
		*lst = tmp;
	else
		last_env(*lst)->next = tmp;
}

// it stores char **envp into and linked list-list with memebers key, value for each node.
void	make_env(char **env, t_envp **lst, int i, int j)
{
	int		toggle;
	t_envp	*tmp;

	while (env[i])
	{
		j = 0;
		toggle = 1;
		tmp = safe_alloc(sizeof(t_envp), 0);
		if (!tmp)
			exit (EXIT_FAILURE);
		while(env[i][j])
		{
			if (env[i][j] == '=' && toggle)
			{
				tmp->key = safe_substr(env[i], 0, j);
				tmp->value = safe_substr
				(env[i], j + 1, ft_strlen(env[i] + j + 1));
				toggle = 0;
			}
			j++;
		}
		add_to_envp(lst, tmp);
		i++;
	}
}