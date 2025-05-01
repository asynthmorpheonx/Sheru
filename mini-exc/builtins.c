#include "minishell.h"

// // export PATH+=:/new/path PATH=VALUE

void	ft_export(t_data *cmd, t_env *env) // need a restructing for export's own struct that contains only its data
{
	int	i;
	t_export	*data;

	data = cmd->export_data;
	if (!cmd->cmd[1]) // printing all the variables (this is done and don't ever touch it)
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

void	ft_unset(t_data *data, t_env **env)
{
	t_env *(prev), *(current);

	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, data->cmd[1]) == 0)
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
void	ft_exit(t_data *data)
{
	int	code;

	code = ft_atoi(data->cmd[1]);
	// free all the memory or call the garbage collector to dod so
	if(!code) // check the exit code if it's valid or not
		exit(0);
	exit(code);
}

//absoult path : /home/user/Documents
//relative path : ../Downloads / ./Downloads

void	ft_cd(t_data *data, t_env *env)
{
	char	*path;

	if (getcwd(data->oldpwd, sizeof(data->oldpwd)) != NULL)
		set_env_var(&env, "OLDPWD", data->oldpwd);
	else
		perror("getcwd");
	if (!data->cmd[1] || data->cmd[1][0] == '\0')
		path = get_home(env);
	else
		path = data->cmd[1];
	if (chdir(path) != 0)
		perror("cd");
	if (getcwd(data->pwd, sizeof(data->pwd)) != NULL)
		set_env_var(&env, "PWD", data->pwd);
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
