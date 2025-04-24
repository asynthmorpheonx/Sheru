#include "minishell.h"

void    free_things(char *one, char **two, char *msg, int check) // maight delet later
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

void	git_dollar(char *str, t_env *env)
{
	int		check;
	
	check = 1;
	while (env && check)
	{
		if (ft_strcmp(str, env->key) == 0)
		{
			printf("%s", env->value);
			check = 0;
		}
		env = env->next;
	}
}

void	echo_print(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;
	if(str[0] == '"' && str[len - 1] == '"') // check how i should deal with one "
		printf("%s", str);
	else
	{
		while(str[i])
		{
			if(str[i] == '\\')
				i++;
			write(1, &str[i], 1);
			i++;
		}
	}
}

void	sort_tenv(char **env)
{
	char	*tmp;
	
	int (i), (u);
	i = 0;
	while (env[i])
	{
		u = i + 1;
		while(env[u])
		{
			if (ft_strcmp(env[u], env[i]) < 0)
			{
				tmp = env[u];
				env[u] = env[i];
				env[i] = tmp; 
			}
			u++;
		}
		i++;
	}
}