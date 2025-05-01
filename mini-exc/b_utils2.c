#include "minishell.h"

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