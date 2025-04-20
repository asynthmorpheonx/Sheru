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

void	ft_export(t_cmd *cmd_list, t_env *env) // need a restructing for export's own struct that contains only its data
{
	t_export	*data;

	if(!cmd_list->cmd_flag[0])
	{
		export_print(env);
	}
	else
	{
		if (!data)
			return ;
		while(data)
		{
			set_env_var(&env, data->var, data->value);
			data = data->next;
		}
	}
}
void	ft_unset(t_cmd *cmd_list, t_env **env)
{
	t_env *(prev), *(current);

	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, cmd_list->var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else 
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}
void	ft_exit(t_cmd *cmd_list)
{
	// free all the memory or call the garbage collector to dod so
	if(!cmd_list->code) // check the exit code if it's valid or not
		exit(0);
	exit(cmd_list->code);
}
void	ft_cd(t_cmd *cmd_list, t_env *env)
{
	char	*path;
	t_cd 	*x;

	if (!(x = malloc(sizeof(t_cd))))
		return ;
	if (getcwd(x->oldpwd, sizeof(x->oldpwd)) != NULL)
		set_env_var(&env, "OLDPWD", x->oldpwd);
	else
		perror("getcwd");
	if(cmd_list->cmd_flag[0])
	{
		if (chdir(cmd_list->cmd_flag[0]) != 0)
			perror("cd");
	}
	else
	{
		path = getenv("HOME");
		if(chdir(path) != 0)
			perror("cd");
	}
	if (getcwd(x->pwd, sizeof(x->pwd)) != NULL)
			set_env_var(&env, "PWD", x->pwd);
	else
		perror("getcwd");
	free(x);
}