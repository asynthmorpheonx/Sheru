/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/04/18 12:48:13 by hoel-mos         ###   ########.fr       */
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
// builtins that i can run in the parent
// cd , exit, export, unset
//----------------------------------
// builtins that i can't 
// pwd, wcho, env 


void	 execute_single(t_cmd *cmd_list, t_env *env, int input_fd, int checker)
{
	char *(path), **(args);
	var()->pid = fork();
	if (var()->pid == 0)
	{
		if (cmd_list->infd != STDIN_FILENO)
		{
			dup2(cmd_list->infd, STDIN_FILENO);
			close(cmd_list->infd);
		}
		if(cmd_list->outfd != STDOUT_FILENO)
		{
			dup2(cmd_list->outfd, STDOUT_FILENO);
			close(cmd_list->outfd);
		}
		path = get_path(cmd_list->cmd);
		args = build_args(cmd_list->cmd, cmd_list->cmd_flag);
		execve(path, args, env_to_array(env));
		args = ft_free_array(args);
		exit(1);
	}
	else if(var()->pid > 0)
		waitpid(var()->pid, &var()->status, 0);
}
int	builtin_check(char *cmd)
{
	char  **builtins;

	builtins = ft_split("echo env pwd cd export unset exit", ' ');
	var()->index = 0;
	while(builtins[var()->index])
	{
		if (ft_strcmp(cmd, builtins[var()->index]) == 0 &&
			(var()->index >= 0 && var()->index <= 2))
		{
			builtins = ft_free_array(builtins);
			return (1); // for "echo env pwd" that needs fork
		}
		else if (ft_strcmp(cmd, builtins[var()->index]) == 0 &&
			(var()->index >= 3 && var()->index <= 6))
		{
			builtins = ft_free_array(builtins);
			return (2); // for "cd, export, unset, exit" that i need to take care of in another function
		}
		var()->index++;
	}
	builtins = ft_free_array(builtins);
	return (0);
}

void	ft_ceue(t_cmd *cmd_list, t_env *env)
{
	if(ft_strcmp(cmd_list->cmd, "cd") == 0)
	{
		ft_cd(cmd_list, env);
	}
	else if(ft_strcmp(cmd_list->cmd, "export") == 0)
	{
		
	}
	else if(ft_strcmp(cmd_list->cmd, "unset") == 0)
	{
		
	}
	else if(ft_strcmp(cmd_list->cmd, "exit") == 0)
	{
		
	}
}

void	check_cmd(t_cmd *cmd_list, t_env *env, int fd)
{
	int	check;

	check = builtin_check(cmd_list->cmd);
	if(check == 1) // to run in(outside) the parent
	{
		ft_ceue(cmd_list, env);
	}
	else if (check == 2) // means i can run it in the child
		execute_single(cmd_list->cmd, env, STDIN_FILENO, 0);
	else
		execute_single(cmd_list->cmd, env, STDIN_FILENO, 1);
}

int execute_commands(t_cmd *cmd_list, t_env *env) //beggining
{
    if (!cmd_list)
		return 0;
    // if (cmd_list->next)
    //     execute_pipeline(cmd_list, env);
	else 
        check_cmd(cmd_list, env,  STDIN_FILENO);
    //return get_exit_status();  // From global or waitpid result
}