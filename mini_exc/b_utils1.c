#include "minishell.h"

char *word(char *str)
{
	int i, len;
	char *buf;

	i = 0;
	len = 0;
	while(str[i] && str[i] != '=')
	{
		len++;
		i++;
	}
	buf = safe_alloc(len + 1 , 0);
	i = 0;
	while(str[i] && str[i] != '=')
	{
		buf[i] = str[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
//###################################################################
//
//                  27 line 
//
//###################################################################
void	set_env_var(t_env **env, const char *key, const char *value)
{
	t_env *(current), *(prev), *(new_var);
	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if ( ft_strcmp(word(current->key), key) == 0)
		{
			free(current->value); // maight need to be removed through garbage collector
			current->value = ft_strdup(value);
			return;
		}
		prev = current;
		current = current->next;
	}
	new_var = safe_alloc(sizeof(t_env), 0);
	if (!new_var)
		return ;
	new_var->key = ft_strdup(key);
	if (value)
		new_var->value = ft_strdup(value);
	else
		new_var->value = NULL;
	new_var->next = NULL;
	if (prev != NULL)
		prev->next = new_var;
	else
		*env = new_var;
}

char	*ft_envcat(char *dest, const char *src)
{
	char	*buf;
	int	len;

	len = ft_strlen(dest) + ft_strlen(src);
	buf = safe_alloc(sizeof(char) * len + 1, 0);
	if(!buf)
		return (NULL);
	ft_strcpy(buf, dest);
	ft_strcat(buf, src);
	return (buf);	
}

void	ft_var_append(t_env *env, char *var, const char *appe)
{
	char	*va;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, var) == 0)
		{
			va = ft_envcat(tmp->value, appe);
			free(tmp->value);
			tmp->value = va;
			return ;
		}
		tmp = tmp->next;
	}
	set_env_var(&env, var, appe); // if the var not exist we creat it and give it the value appe
}

char	*get_home(t_env *env)
{
	while(env)
	{
		if(ft_strncmp(env->key, "HOME", 3) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}