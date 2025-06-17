
#include "mini_shell.h"


t_exutil	*executer(void)
{
	static t_exutil	pp;

	return (&pp);
}

void ft_free_array(char **arr)
{
	int	i;

	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

int count_words(char *flags)
{
	int (i), (u);

	i = 0;
	u = 0;
	while (flags[i])
	{
		if (flags[i] == ' ' || (flags[i] >= 9 && flags[i] <= 13))
			i++;
		else
		{
			u++;
			while (flags[i] != ' ' && !(flags[i] >= 9 && flags[i] <= 13))
				i++;
		}
	}
	return (u);
}
void	wait_for_childs(void)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < executer()->c_count)
	{
		if (offs()->pids[i])
		{
			waitpid(offs()->pids[i], &status, 0);
			code_setter(WEXITSTATUS(status));
		}
		i++;
	}
	free(offs()->pids);
}
