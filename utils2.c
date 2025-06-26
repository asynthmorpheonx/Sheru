/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:28:45 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/25 20:36:44 by mel-mouh         ###   ########.fr       */
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
		ft_export(data);
	else if (!ft_strcmp(data->cmd[0], "unset"))
		ft_unset(data, env);
	else if (!ft_strcmp(data->cmd[0], "exit"))
		ft_exit(data);
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
	if (ind)
	{
		if (ind % 2 == 0)
			dup2(offs()->spi[0], 0);
		else
			dup2(offs()->fpi[0], 0);
	}
	if (cmd->next)
	{
		if (ind % 2 == 0)
			dup2(offs()->fpi[1], 1);
		else
			dup2(offs()->spi[1], 1);
	}
	close(offs()->fpi[1]);
	close(offs()->fpi[0]);
	close(offs()->spi[1]);
	close(offs()->spi[0]);
}

bool	safer_fork(pid_t process_id, int ind, t_data *cmd)
{
	if (process_id == -1)
		ult_exit();
	if ((!process_id && !cmd->cmd) || !process_id)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		return (true);
	}
	else
		offs()->pids[ind] = process_id;
	return (false);
}

void	redir_msg_err(int err_num, char *str)
{
	if (err_num != 3)
		ft_putstr_fd("sheru: ", 2);
	if (err_num == 1)
		perror(str);
	else if (err_num == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
	else if (err_num == 3)
	{
		ft_putstr_fd("cd: error retrieving current directory:", 2);
		ft_putstr_fd(" getcwd: cannot access parent directories", 2);
		ft_putendl_fd(": No such file or directory", 2);
	}
}
