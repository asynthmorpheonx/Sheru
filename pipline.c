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
	if (executer()->c_count - 1)
		free(pipes);
	offs()->pipes = NULL;
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
		if (!*cmd->cmd)
			err(*cmd->cmd, status, 0);
		else
			err("''", status, 0);
		close_pipes(offs()->pipes);
		clear_container();
		return (status);
	}
	anvp = env_to_array(*envp());
	execve(path, cmd->cmd, anvp);
	perror("sheru");
	ult_exit();
	return (0);
}

void	child_exec(t_data *cmd)
{
	int	status;

	status = 0;
	handle_pipes(cmd, executer()->ind);
	if (!redirect(cmd))
		return (free(offs()->pids), close_pipes(offs()->pipes), exit(1));
	if (cmd->cmd && *cmd->cmd && !executer()->is_builtin)
	{
		status = execute_pipeline(cmd);
		if (status)
			return (free(offs()->pids), exit(status));
	}
	else if (cmd->cmd && *cmd->cmd)
	{
		ft_ceue(cmd, envp());
		close_pipes(offs()->pipes);
	}
	free(offs()->pids);
	clear_container();
	exit(ft_atoi(exit_code()));
}
