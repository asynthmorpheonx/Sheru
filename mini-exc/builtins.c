#include "minishell.h"

void	ft_export(t_cmd *cmd_list, t_env *env)
{
	if(!cmd_list->cmd_flag)
	{
		while(env)
		{
			printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	else
		set_env_var(&env, cmd_list->var, cmd_list->value);
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
void	ft_unset(t_cmd *cmd_list, t_env **env)
{
	t_env	*(prev), *(current);
	while(env)
	{
		if(ft_strcmp((*env)->key, cmd_list->var) == 0)
		{
			if(prev)
				prev->next = (*env)->next;
			free((*env)->key);
			free((*env)->value);
			free(*env);
		}
		prev = env;
		env = (*env)->next;
	}
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
	if(cmd_list->cmd_flag)
	{
		if (chdir(cmd_list->cmd_flag) != 0)
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