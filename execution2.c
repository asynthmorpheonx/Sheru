/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:18:15 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/20 17:23:34 by hoel-mos         ###   ########.fr       */
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

char	*get_path(char *cmd, int *error_status)
{
	int		i;
	char	*path;
	char	*path_value;
	char	**paths;

	i = 0;
	*error_status = 127;
	path_value = key_value("PATH");
	if (!*cmd ||
		(*cmd != '/' && *cmd != '.' && *cmd != '~' && !*path_value))
		return (NULL);
	else if (*cmd == '/' || *cmd == '.' || *cmd == '~')
		return (path_already(cmd, error_status));
	paths = ft_split(key_value("PATH"), ':');
	if (!paths)
		ult_exit();
	while(paths[i])
	{
		path = path_join(paths[i], cmd, error_status);
		if (path)
			return (ft_free_array(paths), path);
		free(path);
		i++;
	}
	return (ft_free_array(paths), NULL);
}
