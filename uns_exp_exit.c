/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uns_exp_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:17:08 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:47:25 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	ft_exit(void)
{
	close_pipes();
	if (offs()->pids)
		free(offs()->pids);
	clear_container();
	exit(EXIT_SUCCESS);
}

void	ft_unset(t_data *data, t_env **env)
{
	t_env	*prev;
	t_env	*current;

	prev = NULL;
	current = *env;
	while (current)
	{
		if (!ft_strcmp(current->key, data->cmd[1]))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			delete_one(current->key);
			delete_one(current->value);
			delete_one(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
