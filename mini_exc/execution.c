/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/04 15:59:55 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	builtin_check(char *cmd)
{
	char	**builtins;
	int		index;

	builtins = ft_split("echo env pwd cd export unset exit", ' ');
	index = 0;
	while (index < 7)
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
		{
			ft_free_array(builtins);
			return (1);
		}
		index++;
	}
	ft_free_array(builtins);
	return (0);
}

void	ft_ceue(t_data *data, t_env **env)
{
	if (ft_strcmp(data->cmd[0], "cd") == 0)
		ft_cd(data, env);
	else if (ft_strcmp(data->cmd[0], "export") == 0)
		ft_export(data, env);
	else if (ft_strcmp(data->cmd[0], "unset") == 0)
		ft_unset(data, env);
	else if (ft_strcmp(data->cmd[0], "exit") == 0)
		ft_exit(data);
	else if (ft_strcmp(data->cmd[0], "echo") == 0)
		ft_echo(data);
	else if (ft_strcmp(data->cmd[0], "env") == 0)
		ft_env(env);
	else if (ft_strcmp(data->cmd[0], "pwd") == 0)
		ft_pwd();
	if (offs()->redir == 1)
	{
		dup2(offs()->out_backup, STDOUT_FILENO);
		offs()->redir = -1;
	}
	else if (offs()->redir == 2)
	{
		dup2(offs()->in_backup, STDIN_FILENO);
		offs()->redir = -1; 
	}
}

void execute_commands(t_data *cmd) //beggining
{
	// printf("############################## EXECUTION STARTED #################################\n");
	t_data *tmp;
	offs()->redir = -1;
	offs()->in_backup = dup(STDIN_FILENO);
	offs()->out_backup = dup(STDOUT_FILENO);
	if (!cmd)
		return ;
	tmp = cmd;
	if (tmp->next)
	{
		execute_pipeline(tmp, envp());

	}
	else
	{
		if (builtin_check(tmp->cmd[0]))
		{
			if (cmd->file.infile || cmd->file.outfile)
			{
				printf("herdoc enter redirection\n");	
				redirect(cmd);
			}
			ft_ceue(tmp, envp());
		}
		else
			execute_pipeline(tmp, envp());
		fprintf(stderr, "here we are %s \n", *cmd->cmd);
	}
	close(offs()->in_backup);
	close(offs()->out_backup);
	// clear_container();
	//reset
}