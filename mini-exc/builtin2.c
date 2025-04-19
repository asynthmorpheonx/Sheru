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

void	ft_echo(t_cmd *cmd_list, t_env *env)
{
	char	*var;
	int	i;
	
	i = 0;
	while (cmd_list->cmd_flag[i])
	{
		if (cmd_list->cmd_flag[i][0] == '$')
		{
			git_dollar(cmd_list->cmd_flag[i] + 1, env);
			if (cmd_list->cmd_flag[i + 1])
				printf(" ");
		}
		else
		{
			printf("%s", cmd_list->cmd_flag[i]);
			if (cmd_list->cmd_flag[i + 1])
				printf(" ");
		}
		i++;
	}
	if (ft_strcmp(cmd_list->cmd_flag[0], "-n") != 0)
		printf("\n");
}