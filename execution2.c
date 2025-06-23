/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:18:15 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/23 16:36:03 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int envcount(t_env *env)
{
    int count;
	t_env *current;

	current = env;
    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

void catcpy(char *tmp, t_env *current)
{
    ft_strcpy(tmp, current->key);
    ft_strcat(tmp, "=");
	if (current->value)
    	ft_strcat(tmp, current->value);
    else
		ft_strcat(tmp, "");
}

char    **env_to_array(t_env *ptr)
{
	int	i;
	char	**anvp;

	i = 0;
	anvp = safe_alloc(sizeof(char *)
		* (envcount(ptr) + 1), 0);
	if (!anvp)
		ult_exit();
	while(ptr)
	{
		anvp[i] = safe_alloc(ft_strlen(ptr->key)
			+ ft_strlen(ptr->value) + 2, 0);
		if (!anvp[i])
			ult_exit();
		catcpy(anvp[i], ptr);
		i++;
		ptr = ptr->next;
	}
	return (anvp);
}

char	*path_join(char *path, char *cmd, int *status)
{
	char	*buff;

	buff = ft_strjoin(path, "/");
	buff = ft_gnl_strjoin(buff, cmd);
	if (!access(buff, F_OK))
	{
		if (!access(buff, X_OK))
			return (buff);
		*status = 126;
	}
	else
		*status = 127;
	free(buff);
	return(NULL);
}

char	*path_already(char *cmd, int *status)
{
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (ft_strdup(cmd));
		else
		{
			*status = 126;
			return (NULL);
		}
	}
	*status = 127;
	return (NULL);
}

bool	check_f_path(char *cmd)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

char	*check_from_path(char *cmd, int *err_status)
{
	char	*path;
	int		i;
	char	**paths;

	i = 0;
	paths = ft_split(key_value("PATH"), ':');
	if (!paths)
		ult_exit();
	while(paths[i])
	{
		path = path_join(paths[i], cmd, err_status);
		if (path)
			return (ft_free_array(paths), path);
		free(path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}

char	*get_path(char *cmd, int *error_status)
{
	struct stat	st;

	*error_status = 127;
	if (!*cmd || !ft_strncmp("..", cmd, 3)
		|| !ft_strncmp(".", cmd, 2))
		return (NULL);
	if (check_f_path(cmd))
	{
		if (access(cmd, F_OK))
		{
			*error_status = 5;
			return (NULL);
		}
		if (stat(cmd, &st) == -1)
			err("stat", 3, 1);
		if (S_ISDIR(st.st_mode))
			*error_status = 6;
		else
			return (path_already(cmd, error_status));
	}
	else
		return (check_from_path(cmd, error_status));
	return (NULL);
	
}
