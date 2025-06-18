/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:18:15 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/18 22:20:39 by mel-mouh         ###   ########.fr       */
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

char	*path_join(char *path, char *cmd)
{
	char	*buff;
	int		len;
	int		i;
	int		u;
	
	len = ft_strlen(path) + ft_strlen(cmd);
	buff = malloc(sizeof(char) * (len + 2));
	i = 0;
	u = 0;
	if (!buff)
		ult_exit();
	while (path[u])
		buff[i++] = path[u++];
	buff[i++] = '/';
	u = 0;
	while (cmd[u])
		buff[i++] = cmd[u++];
	buff[i] = '\0';
	return (buff);
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
	int	i;

	char **(path_buf), *(cmd_path), *(path_copy);
	if (*cmd == '/' || *cmd == '.' || *cmd == '~')
		return (path_already(cmd, error_status));
	cmd_path = key_value("PATH");
	path_buf = ft_split(cmd_path, ':');
	i = 0;
	while(path_buf[i])
	{
		path_copy = path_join(path_buf[i], cmd);
		if (!access(path_copy, F_OK))
		{
			if (!access(path_copy, X_OK))
				return (ft_free_array(path_buf), path_copy);
			*error_status = 126;
			return (ft_free_array(path_buf), NULL);
		}
		free(path_copy);
		i++;
	}
	ft_free_array(path_buf);
	*error_status = 127;
	return (NULL);
}
