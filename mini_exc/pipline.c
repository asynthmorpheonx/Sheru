#include "mini_shell.h"

void	close_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < executer()->c_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);		
}

int	execute_pipeline(t_data *cmd)
{
	char	*path;
	char	**anvp;
	int		status;

	status = 0;
	path = get_path(*cmd->cmd, &status);
	if (!path)
	{
		err(*cmd->cmd, status, 0);
		close_pipes(offs()->pipes);
		clear_container();
		return (status);
	}
	anvp = env_to_array(envp());
	execve(path, cmd->cmd, anvp);
	perror("sheru");
	ult_exit();
	return (0);
}
