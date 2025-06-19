/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/19 20:43:21 by mel-mouh         ###   ########.fr       */
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
		offs()->in_backup = 0;
	}
	if (offs()->out_backup)
	{
		dup2(offs()->out_backup, 1);
		close(offs()->out_backup);
		offs()->out_backup = 0;
	}
}

void execute_command(t_data *cmd)
{
	executer()->ind = 0;
	executer()->c_count = node_count();
	executer()->is_builtin = false;
	make_pids(executer()->c_count);
	if (cmd->next)
			make_pipe(executer()->c_count);
	while (cmd)
	{
		if (cmd->cmd)
			executer()->is_builtin = builtin_check(*cmd->cmd);
		if (!cmd->next && executer()->is_builtin && !executer()->ind)
			exec_builtin(cmd);
		else if (safer_fork(fork(), executer()->ind, cmd))
			child_exec(cmd);
		executer()->ind++;
		cmd = cmd->next;
	}
	if (offs()->pipes)
		close_pipes(offs()->pipes);
	wait_for_childs();
	close_herdoc_ports();
}
