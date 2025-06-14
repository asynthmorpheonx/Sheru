#include "mini_shell.h"

static int	count_commands(t_data *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count++;
		cmd = cmd->next;
	}
	return (count);
}

static void create_pipes(int cmd_count)
{
	int	i;

	if (cmd_count <= 1)
		return ;
	offs()->pipes = malloc(sizeof(int *) * (cmd_count - 1));
	if (!offs()->pipes)
		return ;
	i = 0;
	while (i < cmd_count - 1)
	{
		offs()->pipes[i] = malloc(sizeof(int) * 2);
		if (!offs()->pipes[i])
		{
			while (--i >= 0)
				free (offs()->pipes[i]);
			free (offs()->pipes);
			return ;
		}
		if (pipe(offs()->pipes[i]) == -1)
		{
			while (i >= 0)
				free(offs()->pipes[i--]);
			free(offs()->pipes);
			err("pipe", 3);
		}
		i++;
	}
}

static void	free_pipes(int **pipes, int pipe_count)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

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

static void	setup_child_fds(int **pipes, int cmd_index, int cmd_count)
{
	if (cmd_index > 0)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	if (cmd_index < cmd_count - 1)
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	close_pipes(pipes, cmd_count - 1);
}

static void	child_proc(t_data *cmd, t_env **env, int **pipes, int cmd_index, int cmd_count)
{
	char *path;
	int	status;

	status = 0;
	setup_child_fds(pipes, cmd_index, cmd_count);
	if (cmd->file.infile || cmd->file.outfile)
		redirect(cmd);
	if (builtin_check(cmd->cmd[0]))
	{
		ft_ceue(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		path = get_path(cmd->cmd[0], &status);
		if (path)
		{
			execve(path, cmd->cmd, env_to_array(env));
		}// when calling container from here or when calling err the container tryes to applye a none valid free
		else
		{
			ft_putstr_fd(cmd->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
}

void	execute_pipeline(t_data *cmd, t_env **env)
{
	int		cmd_count;
	pid_t	*pids;
	int		i;
	int		status;

	cmd_count = count_commands(cmd);
	create_pipes(cmd_count);
	pids = malloc(sizeof(pid_t) * cmd_count);
	if (!pids)
		err("malloc", 3);
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			err("fork", 3);
		if (pids[i] == 0)
			child_proc(cmd, env, offs()->pipes, i, cmd_count);
		cmd = cmd->next;
		i++;
	}
	close_pipes(offs()->pipes, cmd_count - 1);
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	free_pipes(offs()->pipes, cmd_count - 1);
	free(pids);
}



