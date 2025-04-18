/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:31:33 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/04/16 18:34:51 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_var *var()
{
	t_var var;
	return (&var);
}
int count_words(char *flags)
{
	int (i), (u);

	i = 0;
	u = 0;
	while(flags[i])
	{
		if(flags[i] == ' ' || (flags[i] >= 9 && flags[i] <= 13))
			i++;
		else
		{
			u++;
			while(flags[i] != ' ' && !(flags[i] >= 9 && flags[i] <= 13))
				i++;
		}
	}
	return (u);
}

char **build_args(char *cmd, char *cmd_flag)
{
	char    **args;
	char    **split_flags;
	int     i;
	int     count;

	// Count total arguments (cmd + split flags)
	split_flags = ft_split(cmd_flag, ' ');
	count = 1 + count_words(cmd_flag); // cmd + flags
	
	args = malloc(sizeof(char *) * (count + 1)); // +1 for NULL
	if (!args)
		return NULL;
	// First argument is the command
	args[0] = ft_strdup(cmd);
	// Add split flags
	i = 1;
	while (split_flags && *split_flags)
	{
		args[i++] = ft_strdup(*split_flags);
		split_flags++;
	}   
	args[i] = NULL; // NULL terminate array
	return args;
}
int	builtin_check(char *cmd)
{
	char  **builtins;
	int	index;

	builtins = (char *[]){"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	index = 0;
	while(builtins[index])
	{
		if(ft_strcmp(cmd, builtins[index]) == 0)
			return (1);
		index++;
	}
	return (0);
}

void    free_things(char *one, char **two, char *msg, int check)
{
    if(check == 1)
    {
        struc()->index = 0;
        while(two[struc()->index])
        {
            free(two[struc()->index]);
            struc()->index++;
        }
        free(two);
    }
    else if(check == 2)
    {
        struc()->index = 0;
        perror(msg);
        while(two[struc()->index])
        {
            free(two[struc()->index]);
            struc()->index++;
        }
        free(two);
        free(one);
    }
    else
        perror(msg);
    exit(1);
}

char *ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	retuen (NULL);
}

int envcount(t_env *current)
{
    int count;

    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}
void    catcpy(char *tmp, char *str, t_env *current)
{
    ft_strcpy(tmp, current->key);
    ft_strcat(tmp, str);
    ft_strcat(tmp, current->value);
}

char    **env_to_array(t_env *env)
{
    t_env   *current;

    char    **(arr), *(tmp);
    int     (count), (i);
    current = env;
    count = envcount(current);
    arr = (char **)malloc(sizeof(char *) * (count + 1));
    if (!arr)
        return (NULL);
    i = 0;
    current = env;
    while (current)
    {
        if (!(tmp  = (char *)malloc(ft_strlen(current->key) + ft_strlen(current->value) + 2)))
            return(ft_free_array(arr));
        catcpy(tmp, "=", current);
        arr[i++] = tmp;
        current = current->next;
    }
    arr[i] = NULL;  // NULL-terminate the array
    return (arr);
}

char	*ft_cat(char *path, char *cmd)
{
	char	*buff;
	
	int	(len), (i), (u);
	len = ft_strlen(path) + ft_strlen(cmd);
	buff = malloc(sizeof(char) * (len + 2));
	if (!buff)
		return (NULL);
	i = 0;
	u = 0;
	while(path[u])
		buff[i++] = path[u++];
	buff[i++] = '/';
	u = 0;
	while(cmd[u])
		buff[i++] = cmd[u++];
	buff[i] = '\0';
	return (buff);
}

char	*get_path(char *cmd)
{
	char	**path_buf;
	int	i;

	var()->cmd_path = getenv("PATH");
	path_buf = ft_split(var()->cmd_path, ':');
	i = 0;
	while(path_buf[i])
	{
		var()->path_copy = ft_cat(path_buf[i], cmd);
		if (access(var()->path_copy, X_OK) == 0)
		{
			path_buf = ft_free_array(path_buf);
			return (var()->path_copy);
		}
		free(var()->path_copy);
		i++;
	}
	return (ft_free_array(path_buf));
}
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

void	 execute_single(t_cmd *cmd_list, t_env *env, int input_fd)
{
	char *(path), **(args);
	if (builtin_check(cmd_list->cmd))
			printf("yes it's builtin\n");
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
}




int execute_commands(t_cmd *cmd_list, t_env *env) //beggining
{
    if (!cmd_list)
		return 0;
    // if (cmd_list->next)
    //     execute_pipeline(cmd_list, env);
	else 
        execute_single(cmd_list, env,  STDIN_FILENO);
    return get_exit_status();  // From global or waitpid result
}