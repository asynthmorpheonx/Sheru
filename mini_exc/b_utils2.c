#include "minishell.h"

int	ft_varcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] != '=' && s2[i] != '=')
	{
		if(s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i] - s2[i]);
}

void	export_print(t_env *env)
{
	char	**tenv;
	t_env	*tmp;
	
	int (i), (check);
	tenv = env_to_array(env);
	sort_tenv(tenv);
	i = 0;
	while (tenv[i])
	{
		tmp = env;
		while (tmp)
		{
			check = ft_varcmp(tmp->key, tenv[i]);
			if (check == 0)
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

