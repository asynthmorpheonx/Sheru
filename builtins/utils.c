#include "mini_shell.h"

t_offs *offs(void)
{
	static t_offs x;

	return (&x);
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

void err(char *str, int error_status, bool ex_it)
{
	if (error_status == 4)
		ft_putstr_fd("sheru: ", 2);
	if (error_status != 3)
		ft_putstr_fd(str, 2);
	if (error_status == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (error_status == 2)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (error_status == 3)
		perror(str);
	else if (error_status == 4)
		ft_putstr_fd(": ambiguous redirect\n", 2);
	else if (error_status == 127)
		ft_putstr_fd(": command not found\n", 2);
	else if (error_status == 126)
		ft_putstr_fd(": permission denied\n", 2);	
	clear_container();
	if (ex_it)
		exit(EXIT_FAILURE);
}
