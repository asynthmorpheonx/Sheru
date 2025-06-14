#include "mini_shell.h"

// static int	count_commands(t_data *cmd)
// {
// 	int	count;

// 	count = 0;
// 	while (cmd)
// 	{
// 		count++;
// 		cmd = cmd->next;
// 	}
// 	return (count);
// }

// static void	free_pipes(int **pipes, int pipe_count)
// {
// 	int	i;

// 	if (!pipes)
// 		return ;
// 	i = 0;
// 	while (i < pipe_count)
// 	{
// 		free(pipes[i]);
// 		i++;
// 	}
// 	free(pipes);
// }

static void	close_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	execute_pipeline(t_data *cmd, int pcount)
{
	char	*path;
	char	**anvp;
	int		status;

	status = 0;
	path = get_path(*cmd->cmd, &status);
	if (!path)
	{
		err(*cmd->cmd, status);
		close_pipes(offs()->pipes, pcount);
		clear_container();
		exit(status);
	}
	anvp = env_to_array(envp());
	execve(path, cmd->cmd, anvp);
	perror("sheru");
	ult_exit();
}



