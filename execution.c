/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sheru.h"

int	builtin_check(char *cmd)
{
	return (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd"));
}

int	node_count(void)
{
	int		count;
	t_data	*tmp;

	count = 0;
	tmp = *box();
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

void	exec_builtin(t_data *cmd)
{
	if (cmd->file.infile || cmd->file.outfile)
	{
		offs()->in_backup = dup(0);
		offs()->out_backup = dup(1);
	}
	if (redirect(cmd, false))
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

void	execute_command(t_data *cmd)
{
	executer()->ind = 0;
	executer()->c_count = node_count();
	executer()->is_builtin = false;
	make_pids(executer()->c_count);
	make_pipe();
	while (cmd)
	{
		if (cmd->next)
			pipe_indexing();
		if (cmd->cmd && *cmd->cmd)
			executer()->is_builtin = builtin_check(*cmd->cmd);
		if (!cmd->next && executer()->is_builtin && !executer()->ind)
			exec_builtin(cmd);
		else if (safer_fork(fork(), executer()->ind, cmd))
			child_exec(cmd);
		executer()->ind++;
		cmd = cmd->next;
	}
	close_pipes();
	wait_for_childs();
	close_herdoc_ports();
}
