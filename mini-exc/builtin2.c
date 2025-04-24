#include "minishell.h"

void	ft_echo(t_cmd *cmd_list, t_env *env)
{
	int		i;
	t_echo	*data;
	char	**buff;

	data = cmd_list->echo_data;
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
	if (data->n_check == false)
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