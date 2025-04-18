#include "minishell.h"

t_var *var()
{
	t_var var;
	return (&var);
}

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

char **build_args(char *cmd, char *cmd_flag)
{
	char **(args), **(split_flags);
	int (i), (count);

	// Count total arguments (cmd + split flags)
	split_flags = ft_split(cmd_flag, ' ');
	count = 1 + count_words(cmd_flag); // cmd + flags
	args = malloc(sizeof(char *) * (count + 1)); // +1 for NULL
	if (!args)
		return NULL;
	// First argument is the command
	args[0] = ft_strdup(cmd);
	// Add split flags
	i = 1;
	while (split_flags && *split_flags)
	{
		args[i++] = ft_strdup(*split_flags);
		split_flags++;
	}   
	args[i] = NULL; // NULL terminate array
	return args;
}