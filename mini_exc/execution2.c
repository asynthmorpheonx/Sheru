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
    ft_strcat(tmp, current->value ? current->value : "");  // Prevent crash
}


char    **env_to_array(t_env **env)
{
    t_env   *current;

    char    **(arr), *(tmp);
    int     (count), (i);
    current = *env;
    count = envcount(current);
    arr = (char **)safe_alloc(sizeof(char *) * (count + 1), 0);
    i = 0;
    current = *env;
    while (current)
    {
		if (!(tmp  = safe_alloc(ft_strlen(current->key) + ft_strlen(current->value) + 2, 0 )))
		{
			ft_free_array(arr);
			return(NULL);
		}
        catcpy(tmp, current);
        arr[i++] = tmp;
        current = current->next;
    }
    arr[i] = NULL;
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
		return (ft_strdup(cmd));
	cmd_path = key_value("PATH");
	path_buf = ft_split(cmd_path, ':');
	i = 0;
	while(path_buf[i])
	{
		path_copy = ft_cat(path_buf[i], cmd);
		if (!access(path_copy, F_OK))
		{
			ft_free_array(path_buf);
			if (!access(path_copy, X_OK))
				return (path_copy);
			*error_status = 126;
			return (NULL);
		}
		free(path_copy);
		i++;
	}
	ft_free_array(path_buf);
	*error_status = 127;
	return (NULL);
}
