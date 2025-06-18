#include "mini_shell.h"

void	echo_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
}

bool check_n(char *arg)
{
	int i;

	if (*arg != '-')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	if (i == 1 && !arg[i])
		return (false);
	return (true);
}

void	ft_echo(t_data *cmd)
{
	bool	mode;

	mode = false;
	if (cmd->cmd[1])
		mode = check_n(cmd->cmd[1]);
	if (mode)
	{
		echo_print(cmd->cmd + 2);
	}
	else
	{
		echo_print(cmd->cmd + 1);
		printf("\n");
	}
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
