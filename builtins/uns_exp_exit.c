/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uns_exp_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:17:08 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

bool	exit_arg_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("sheru: exit: ", 2);
			return (err(str, 7, 0), false);
		}
		i++;
	}
	return (true);
}

void	ft_exit(t_data *cmd)
{
	int	exit_nbr;

	exit_nbr = 2;
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		code_setter(1);
		return (ft_putendl_fd("sheru: exit: too many arguments", 2));
	}
	if (cmd->cmd[1] && exit_arg_check(cmd->cmd[1]))
		exit_nbr = ft_atoi(cmd->cmd[1]);
	else if (!cmd->cmd[1])
		exit_nbr = ft_atoi(exit_code());
	close_pipes();
	if (offs()->pids)
		free(offs()->pids);
	clear_container();
	exit(exit_nbr);
}

void	ft_unset(t_data *data, t_env **env)
{
	t_env	*prev;
	t_env	*current;

	code_setter(0);
	if (!data->cmd[1])
		return ;
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
