/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_nd_store_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:01:00 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:33:45 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_env	*last_env(t_env *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_to_envp(t_env **lst, t_env *tmp)
{
	if (!*lst)
		*lst = tmp;
	else
		last_env(*lst)->next = tmp;
}

void	make_env(char **env, t_env **lst, int i, int j)
{
	int		toggle;
	t_env	*tmp;

	while (env[i])
	{
		j = 0;
		toggle = 1;
		tmp = safe_alloc(sizeof(t_env), 0);
		if (!tmp)
			exit (EXIT_FAILURE);
		while (env[i][j])
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
