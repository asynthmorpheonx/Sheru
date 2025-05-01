/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/04/30 16:57:55 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Input redirection (<):
// Takes input from a file instead of the keyboard.
//---------------------------
// Output redirection (>):
// Writes output to a file instead of the terminal (overwrites file).
// ---------------------------
// Append redirection (>>):
// Appends output to the end of a file.
//------------------------
// Heredoc (<<):
// Feed multiline input directly to a command until a delimiter is reached.
// ******************************************************************************* 

int	builtin_check(char *cmd)
{
	char	**builtins;
	int		index;

	builtins = ft_split("echo env pwd cd export unset exit", ' ');
	index = 0;
	while(builtins[index])
	{
		if (ft_strcmp(cmd, builtins[index]) == 0)
		{
			builtins = ft_free_array(builtins);
			return (1);
		}
		index++;
	}
	builtins = ft_free_array(builtins);
	return (0);
}


void	ft_ceue(t_data *data, t_env *env)
{
	if(ft_strcmp(data->cmd[0], "cd") == 0)
		ft_cd(data, env);
	else if(ft_strcmp(data->cmd[0], "export") == 0)
		ft_export(data, env);
	else if(ft_strcmp(data->cmd[0], "unset") == 0)
		ft_unset(data, &env);
	else if(ft_strcmp(data->cmd[0], "exit") == 0)
		ft_exit(data);
	else if(ft_strcmp(data->cmd[0], "echo") == 0)
		ft_echo(data, env);
	else if(ft_strcmp(data->cmd[0], "env") == 0)
		ft_env(env);
	else if(ft_strcmp(data->cmd[0], "pwd") == 0)
		ft_pwd();
}

void	check_cmd(t_data *cmd, t_env *env, int fd)
{
	int	check;

	check = builtin_check(cmd->cmd[0]);
	if(check == 1) // to run in(outside) the parent
	{
		ft_ceue(cmd, env);
	}
	else
		execute_single(cmd, env, STDIN_FILENO);
}

int execute_commands(t_data *cmd, t_env *env) //beggining
{
	t_data *tmp;
	
	int	(index), (last);
    if (!cmd)
		return 0;
    execute_pipeline(cmd, env);
}