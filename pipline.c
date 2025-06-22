#include "mini_shell.h"

void	close_pipes(void)
{
	if (offs()->fpi[1] || offs()->fpi[0])
	{
		if (offs()->fpi[1])
			close(offs()->fpi[1]);
		if (offs()->fpi[0])
			close(offs()->fpi[0]);
	}
	if (offs()->spi[1] || offs()->spi[0])
	{
		if (offs()->spi[1])
			close(offs()->spi[1]);
		if (offs()->spi[0])
			close(offs()->spi[0]);
	}
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
		if (*cmd->cmd)
			err(*cmd->cmd, status, 0);
		else
			err(" ", status, 0);
		if (status == 6)
			status = 126;
		else if (status == 5)
			status = 127;
		close_pipes();
		clear_container();
		return (status);
	}
	anvp = env_to_array(*envp());
	close_pipes();
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
		return (free(offs()->pids), close_pipes(), exit(1));
	if (cmd->cmd && *cmd->cmd && !executer()->is_builtin)
	{
		status = execute_pipeline(cmd);
		if (status)
			return (free(offs()->pids), exit(status));
	}
	else if (cmd->cmd && *cmd->cmd)
	{
		ft_ceue(cmd, envp());
		close_pipes();
	}
	free(offs()->pids);
	clear_container();
	exit(ft_atoi(exit_code()));
}
