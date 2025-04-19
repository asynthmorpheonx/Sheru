#include "minishell.h"

void    free_things(char *one, char **two, char *msg, int check)
{
    if(check == 1)
    {
        struc()->index = 0;
        while(two[struc()->index])
        {
            free(two[struc()->index]);
            struc()->index++;
        }
        free(two);
    }
    else if(check == 2)
    {
        struc()->index = 0;
        perror(msg);
        while(two[struc()->index])
        {
            free(two[struc()->index]);
            struc()->index++;
        }
        free(two);
        free(one);
    }
    else
        perror(msg);
    exit(1);
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
	new_var->value = ft_strdup(value);
	new_var->next = NULL;
	if (prev != NULL)
		prev->next = new_var;
	else
		*env = new_var;
}