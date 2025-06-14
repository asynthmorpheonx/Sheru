/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/14 21:02:14 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	builtin_check(char *cmd)
{
	return (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd"));
}

void	ft_ceue(t_data *data, t_env **env)
{
	if (!ft_strcmp(data->cmd[0], "cd"))
		ft_cd(data, env);
	else if (!ft_strcmp(data->cmd[0], "export"))
		ft_export(data, env);
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

int	node_count(void)
{
	int	count;
	t_data *tmp;

	count = 0;
	tmp = *box();
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

pid_t	*make_pids(void)
{
	pid_t	*ptr;
	int		count;

	count = node_count();
	ptr = malloc(count * sizeof(pid_t) + 1);
	if (!ptr)
		ult_exit();
	ft_bzero(ptr, count * sizeof(pid_t));
	return (ptr);
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

void	exec_builtin(t_data *cmd, int ind)
{
	redirect(cmd, true);
	ft_ceue(cmd, envp());
	handle_pipes(cmd, ind);
	if (offs()->out_backup)
	{
		dup2(offs()->in_backup, 0);
		close(offs()->in_backup);
		offs()->in_backup = 0;
	}
	if (offs()->out_backup)
	{
		dup2(offs()->out_backup, 1);
		close(offs()->out_backup);
		offs()->out_backup = 0;
	}
}

void	exec_non_builtin(t_data *cmd, int ind, pid_t *proc_id, int ccount)
{
	proc_id[ind] = fork();
	if (proc_id[ind] == -1)
		ult_exit();
	if (!proc_id[ind])
	{
		handle_pipes(cmd, ind);
		redirect(cmd, false);
		execute_pipeline(cmd, ccount);
	}
}

static void make_pipe(int c_count)
{
	int	i;

	offs()->pipes = malloc(sizeof(int *) * (c_count - 1));
	if (!offs()->pipes)
		return ;
	i = 0;
	while (i < c_count - 1)
	{
		offs()->pipes[i] = malloc(sizeof(int) * 2);
		if (!offs()->pipes[i])
		{
			while (--i >= 0)
				free (offs()->pipes[i]);
			free (offs()->pipes);
			return ;
		}
		if (pipe(offs()->pipes[i]) == -1)
		{
			while (i >= 0)
				free(offs()->pipes[i--]);
			free(offs()->pipes);
			err("pipe", 3);
		}
		i++;
	}
}

void	wait_for_childs(pid_t *proc_id, int ccount)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < ccount + 1)
	{
		if (!proc_id[i])
			waitpid(proc_id[i], &status, 0);
		code_setter(WEXITSTATUS(status));
		i++;
	}
	free(proc_id);
}

void execute_command(t_data *cmd)
{
	int		i;
	int		ccount;
	pid_t	*proc_id;

	i = 0;
	ccount = node_count();
	proc_id = make_pids();
	if (cmd->next)
		make_pipe(ccount);
	while (cmd)
	{
		if (cmd->cmd && !builtin_check(*cmd->cmd))
			exec_non_builtin(cmd, i, proc_id, ccount);
		else
			exec_builtin(cmd, i);
		i++;
		cmd = cmd->next;
	}
	wait_for_childs(proc_id, ccount);
}
