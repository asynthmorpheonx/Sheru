#include "minishell.h"

// t_var *var()
// {
// 	t_var var;
// 	return (&var);
// }

char *ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	retuen (NULL);
}

int count_words(char *flags)
{
	int (i), (u);

	i = 0;
	u = 0;
	while(flags[i])
	{
		if(flags[i] == ' ' || (flags[i] >= 9 && flags[i] <= 13))
			i++;
		else
		{
			u++;
			while(flags[i] != ' ' && !(flags[i] >= 9 && flags[i] <= 13))
				i++;
		}
	}
	return (u);
}