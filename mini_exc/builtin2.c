#include "mini_shell.h"

void	echo_print(char *str) // test the qooute 
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = 0;	
	if(str[0] == '"' && str[len - 1] == '"') // check how i should deal with one "
		ft_putstr_fd(str, STDOUT_FILENO);
	else
	{
		while(str[i])
		{
			if(str[i] == '\\')
				i++;
			ft_putchar_fd(str[i], STDOUT_FILENO);
			i++;
		}
	}
}

void	check_n(char **buff, int *index, int *check)
{
	int (i),	(u);
	i = 1;
	while (buff[i])
	{
		if (buff[i][0] == '-')
		{
			if (buff[i][1] == 'n')
			{
				u = 1;
				while (buff[i][u] == 'n')
					u++;
				if (buff[i][u] && buff[i][u] != 'n')
				{
					*index = i;
					return ;
				}
				*check = 1;
			}
			else
				return ;
		}
		*index = i;
		i++;
	}
	return ;
}

void	ft_echo(t_data *data)
{
	int (i), (check), (u);
	i = 1;
	check = 0;
	check_n(data->cmd, &i, &check);
	while (data->cmd[i])
	{
		u = i + 1;
		echo_print(data->cmd[i]);
		if (data->cmd[u])
			ft_putchar_fd(32, STDOUT_FILENO);
		i++;
	}
	if (!check) //  0-[echo] 1-[-n..]/[txt]
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	ft_pwd(void)
{
	char	*path;

	if(!(path = getcwd(NULL, 0)))
	{
		//free memory
		clear_container();
		perror("pwd");
	}
	else
		ft_putstr_fd(path, STDOUT_FILENO);
	free(path);
	printf("\n");
}