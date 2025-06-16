/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/16 20:31:45 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_exutil	*executer(void)
{
	static t_exutil	pp;

	return (&pp);
}

int	builtin_check(char *cmd)
{
	return (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd"));
}

void	ft_ceue(t_data *data, t_env **env)
{
	if (!data->cmd)
		return ;
	if (!ft_strcmp(data->cmd[0], "cd"))
		ft_cd(data, env);
	else if (!ft_strcmp(data->cmd[0], "export"))
		ft_export(data, env);
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

void	child_exec(t_data *cmd)
{
	int	status;

	status = 0;
	handle_pipes(cmd, executer()->ind);
	if (!redirect(cmd))
	{
		free(offs()->pids);
		close_pipes(offs()->pipes);
		exit(1);
	}
	if (cmd->cmd && !executer()->is_builtin)
	{
		status = execute_pipeline(cmd);
		if (status)
		{
			free(offs()->pids);
			exit(status);
		}			
	}
	else if (cmd->cmd)
		ft_ceue(cmd, envp());
	free(offs()->pids);
	clear_container();
	exit(EXIT_SUCCESS);
}

static void make_pipe(int c_count)
{
	int	i;

	offs()->pipes = malloc(sizeof(int *) * (c_count - 1));
	if (!offs()->pipes)
		ult_exit();
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
			err("pipe", 3, true);
		}
		i++;
	}
}

void	wait_for_childs(void)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < executer()->c_count)
	{
		if (offs()->pids[i])
		{
			waitpid(offs()->pids[i], &status, 0);
			code_setter(WEXITSTATUS(status));
		}
		i++;
	}
	free(offs()->pids);
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

void	exec_builtin(t_data *cmd)
{
	if (cmd->file.infile || cmd->file.outfile)
	{
		offs()->in_backup = dup(0);
		offs()->out_backup = dup(1);	
	}
	redirect(cmd);
	ft_ceue(cmd, envp());
	if (offs()->in_backup)
	{
		dup2(offs()->in_backup, 0);
		close(offs()->in_backup);
	}
	if (offs()->out_backup)
	{
		dup2(offs()->out_backup, 1);
		close(offs()->out_backup);
	}
}

void execute_command(t_data *cmd)
{
	executer()->ind = 0;
	executer()->c_count = node_count();
	executer()->is_builtin = false;
	if (cmd || cmd->next)
	{
		make_pids(executer()->c_count);
		if (cmd->next)
			make_pipe(executer()->c_count);
	}
	while (cmd)
	{
		if (cmd->cmd)
			executer()->is_builtin = builtin_check(*cmd->cmd);
		if (!cmd->next && executer()->is_builtin && !executer()->ind)
			return (exec_builtin(cmd));
		if (safer_fork(fork(), executer()->ind, cmd))
			child_exec(cmd);
		executer()->ind++;
		cmd = cmd->next;
	}
	if (offs()->pipes)
		close_pipes(offs()->pipes);
	wait_for_childs();
	close_herdoc_ports();
}
