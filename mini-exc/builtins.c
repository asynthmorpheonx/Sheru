#include "minishell.h"

// // export PATH+=:/new/path PATH=VALUE

void	ft_export(t_cmd *cmd_list, t_env *env) // need a restructing for export's own struct that contains only its data
{
	int	i;
	t_export	*data;

	data = cmd_list->export_data;
	if (!cmd_list->eflag_check) // printing all the variables (this is done and don't ever touch it)
		export_print(env);
	while(data)
	{
		if (data->export_check)
			ft_var_append(env, data->export_var, data->export_appe); // append a value to the end of a var value (handle the case where you need to append to an none exitsing var)
		else 
			set_env_var(&env, data->export_var, data->export_value); // modify on the var value  
		data = data->next;
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

//absoult path : /home/user/Documents
//relative path : ../Downloads / ./Downloads

void	ft_cd(t_cmd *cmd_list, t_env *env)
{
	char	*path;
	t_cd 	*x;

	x = cmd_list->cd_data;
	if (getcwd(x->oldpwd, sizeof(x->oldpwd)) != NULL)
		set_env_var(&env, "OLDPWD", x->oldpwd);
	else
		perror("getcwd");
	if (!x->path || x->path[0] == '\0')
		path = get_home(env);
	else
		path = x->path;
	if (chdir(path) != 0)
		perror("cd");
	if (getcwd(x->pwd, sizeof(x->pwd)) != NULL)
		set_env_var(&env, "PWD", x->pwd);
	else
		perror("getcwd");
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			ft_putstr_fd(env->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		env = env->next;
	}
}
