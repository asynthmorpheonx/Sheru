/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:28:45 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/17 23:51:22 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	ft_ceue(t_data *data, t_env **env)
{
	if (!data->cmd)
		return ;
	if (!ft_strcmp(data->cmd[0], "cd"))
		ft_cd(data);
	else if (!ft_strcmp(data->cmd[0], "export"))
		ft_export(data, envp());
	else if (!ft_strcmp(data->cmd[0], "unset"))
		ft_unset(data, env);
	else if (!ft_strcmp(data->cmd[0], "exit"))
		ft_exit();
	else if (!ft_strcmp(data->cmd[0], "echo"))
		ft_echo(data);
	else if (!ft_strcmp(data->cmd[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(data->cmd[0], "pwd"))
		ft_pwd();
}

void	make_pids(int ccount)
{
	pid_t	*ptr;
	
	ptr = malloc((ccount) * sizeof(pid_t));
	if (!ptr)
		ult_exit();
	ft_bzero(ptr, ccount * sizeof(pid_t));
	offs()->pids = ptr;
}

void	handle_pipes(t_data *cmd, int ind)
{
	if (offs()->pipes && *offs()->pipes)
	{
		if (ind)
		{
			dup2(offs()->pipes[ind - 1][0], 0);
			close(offs()->pipes[ind - 1][0]);
			close(offs()->pipes[ind - 1][1]);
		}
		if (cmd->next)
		{
			dup2(offs()->pipes[ind][1], 1);
			close(offs()->pipes[ind][1]);
			close(offs()->pipes[ind][0]);
		}
	}
}

bool	safer_fork(pid_t process_id, int ind, t_data *cmd)
{
	if (process_id == -1)
		ult_exit();
	if ((!process_id && !cmd->cmd) || !process_id)
		return (true);
	else
		offs()->pids[ind] = process_id;
	return (false);
}