	#include "mini_shell.h"

void	ft_export(t_data *cmd, t_env **env)
{
	t_export	*data;

	if (!cmd->cmd[1])
		export_print(env);
	else
	{
		build_export_data(cmd, cmd->cmd[1]);
		data = cmd->export_data;
		if (data->export_check)
			ft_var_append(env, data->export_var, data->export_appe);
		else
			set_env_var(env, data->export_var, data->export_value);
	}
}

void	ft_unset(t_data *data, t_env **env)
{
	t_env *(prev), *(current);
	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strcmp(word(current->key), data->cmd[1]) == 0)
		{
			if (prev)
				prev->next = current->next;
			else 
				*env = current->next;
			delete_one(current->key);// use delete one instead
			delete_one(current->value);// use delete one instead
			delete_one(current);// use delete one instead
			return;
		}
		prev = current;
		current = current->next;
	}
}

void	ft_exit(void)
{
	if (offs()->pipes)
		close_pipes(offs()->pipes);
	if (offs()->pids)
		free(offs()->pids);
	clear_container();
	exit(EXIT_SUCCESS);
}

void	ft_cd(t_data *data, t_env **env)
{
	char	*path;

	if (getcwd(offs()->oldpwd, sizeof(offs()->oldpwd)))
		set_env_var(env, "OLDPWD", offs()->oldpwd);
	else
		perror("getcwd");
	if (!data->cmd[1] || !data->cmd[1][0])
		path = get_home(env);
	else
		path = data->cmd[1];
	if (chdir(path))
		return (perror(path));
	if (getcwd(offs()->pwd, sizeof(offs()->pwd)) != NULL)
		set_env_var(env, "PWD", offs()->pwd);
	else
		perror("getcwd");
}

void	ft_env(t_env **env)
{
	t_env *tmp;

	tmp = *env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			ft_putstr_fd(tmp->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
		}
		tmp = tmp->next;
	}
}
