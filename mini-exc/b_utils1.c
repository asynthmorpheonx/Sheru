#include "minishell.h"

void	export_print(t_env *env)
{
	int		i;
	char	**tenv;
	t_env	*tmp;
	tenv = env_to_array(env);
	sort_tenv(tenv);
	i = 0;
	while(tenv[i]) 
	{
		tmp = env;
		while(tmp)
		{
			if(ft_strcmp(tmp->key, tenv[i]) == 0)
			{
				if (tmp->value)
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else
					printf("declare -x %s\n", tmp->key);
			}
			tmp = tmp->next;
		}
		i++;
	}
	ft_free_array(tenv);
}

void	set_env_var(t_env **env, const char *key, const char *value)
{
	t_env *(current), *(prev), *(new_var);
	current = *env;
	prev = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return;
		}
		prev = current;
		current = current->next;
	}
	new_var = malloc(sizeof(t_env));
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
	buf = malloc(sizeof(char) * len + 1);
	if(!buf)
		return (NULL);
	ft_strcpy(buf, dest);
	ft_strcat(buf, src);
	return (buf);	
}

void	ft_var_append(t_env *env, char *var, char *appe)
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
		if(ft_strcmp(env->key, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}