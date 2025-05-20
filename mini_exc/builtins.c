#include "mini_shell.h"
// // export PATH+=:/new/path PATH=VALUE

//export AH=+LA = "+LA"
//export AH+=LA = "LALA"
//export AH=OUI = "OUI"

void	ft_export(t_data *cmd, t_env **env)
{
	t_export	*data;

	if (!cmd->cmd[1])
		export_print(*env);
	else
	{
		build_export_data(cmd, cmd->cmd[1]);
		data = cmd->export_data;
		if (data->export_check)
			ft_var_append(*env, data->export_var, data->export_appe);
		else
			set_env_var(env, data->export_var, data->export_value);
	}
}

////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//
//
//
//		STILL HAVE A PROBLEM WITH MODIFYING ON THE "ENVIRENMENT" USING EXPORT AND UNSET
//
//
//
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

void	ft_unset(t_data *data, t_env **env)
{
	t_env *(prev), *(current);
	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strcmp(word(current->key), data->cmd[1]) == 0)
		{
			printf("unset received\n");
			if (prev)
				prev->next = current->next;
			else 
				*env = current->next;
			free(current->key);// use delete one instead
			free(current->value);// use delete one instead
			free(current);// use delete one instead
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

	if (getcwd(offs()->oldpwd, sizeof(offs()->oldpwd)) != NULL)
		set_env_var(&env, "OLDPWD", offs()->oldpwd);
	else
		perror("getcwd");
	if (!data->cmd[1] || data->cmd[1][0] == '\0')
		path = get_home(env);
	else
		path = data->cmd[1];
	if (chdir(path) != 0)
		perror("cd");
	if (getcwd(offs()->pwd, sizeof(offs()->pwd)) != NULL)
		set_env_var(&env, "PWD", offs()->pwd);
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
