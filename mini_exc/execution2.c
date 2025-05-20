#include "mini_shell.h"
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
    arr = (char **)safe_alloc(sizeof(char *) * (count + 1), 0);
    if (!arr)
        return (NULL);
    i = 0;
    current = env;
    while (current)
    {
        if (!(tmp  = (char *)safe_alloc(ft_strlen(current->key) + ft_strlen(current->value) + 2, 0 )))
            {
				tmp = ft_free_array(arr);
				return(NULL);
			}
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
	buff = safe_alloc(sizeof(char) * (len + 2), 0);
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
	int	i;
	
	char **(path_buf), *(cmd_path), *(path_copy);
	cmd_path = getenv("PATH");
	path_buf = ft_split(cmd_path, ':');
	i = 0;
	while(path_buf[i])
	{
		path_copy = ft_cat(path_buf[i], cmd);
		if (access(path_copy, X_OK) == 0)
		{
			path_buf[0] = ft_free_array(path_buf);
			return (path_copy);
		}
		free(path_copy);
		i++;
	}
	return (ft_free_array(path_buf));
}