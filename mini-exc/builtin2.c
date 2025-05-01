#include "minishell.h"

void	ft_echo(t_data *data, t_env *env)
{
	int		i;
	char	**buff;

	i = 0; 
	while (data->data[i])
	{
		if (data->data[i][0] == '$')
		{
			git_dollar(data->data[i] + 1, env);
			if (data->data[i + 1])
				printf(" ");
		}
		else
		{
			echo_print(data->data[i]); // ask if you should handle "hello\world"
			if (data->data[i + 1])
				printf(" ");
		}
		i++;
	}
	if (!data->cmd[1])
		printf("\n");
}

void	ft_pwd(void)
{
	char	*path;

	if(!(path = getcwd(NULL, 0)))
	{
		//free memory
		perror("pwd");
	}
	else
		ft_putstr_fd(path, 1);
	free(path);
}