 #include "minishell.h"

void set_env_var(t_env *env, const char *key, const char *value)
{
    t_env *(current), *(prev);
	current = env;
	prev = NULL;
    // Check if the variable already exists
    while (current != NULL)
	{
        if (ft_strcmp(current->key, key) == 0)
		{
            free(current->value);  // Free old value
            current->value = ft_strdup(value);  // Set new value
            return;
        }
        prev = current;
        current = current->next;
    }
    t_env *new_var = malloc(sizeof(t_env));
    new_var->key = ft_strdup(key);  // Allocate memory for the key
    new_var->value = ft_strdup(value);  // Allocate memory for the value
    new_var->next = NULL;
    if (prev != NULL) {
        prev->next = new_var;  // Add new variable to the end of the list
    } else {
        env = new_var;  // If env list is empty, set new_var as the head
    }
}

void	ft_cd(t_cmd *cmd_list, t_env *env)
{
	char	*path;
	t_cd 	*x;

	if (!(x = malloc(sizeof(t_cd))))
		return ;
	if (getcwd(x->oldpwd, sizeof(x->oldpwd)) != NULL)
		set_env_var(env, "OLDPWD", x->oldpwd);
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
			set_env_var(env, "PWD", x->pwd);
	else
		perror("getcwd");
	free(x);
}