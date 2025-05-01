#include "minishell.h"

void	dp2(int *fd0, int *fd1, int check)
{
	if(check)
	{
		dup2(fd0, STDIN_FILENO);
        close(fd0);
	}
	else if(!check)
	{
		dup2(fd1, STDOUT_FILENO);
        close(fd1);
        close(fd0);
	}
}

void	p_arr(int **prev_pipe)
{
	if (prev_pipe[0] != -1)
        close(prev_pipe[0]);
	if (prev_pipe[1] != -1)
    	close(prev_pipe[1]);
}

void	child_proc(t_data *cmd, int *prev, int *curr, t_env *env, t_file *file)
{
	if (file)
		redirect(file);
	else if (prev[0] != -1)
		dp2(prev[0], prev[1], 1);
	else if (cmd->next)
		dp2(curr[0], curr[1], 0);
	execve(get_path(cmd->cmd[0]), cmd->cmd, env_to_array(env));
	err("execve");
}

void	parent_proc(int *prev, int *curr, t_data *cmd)
{
	p_arr(prev);
	if (cmd->next)
	{
		prev[0] = curr[0];
		prev[1] = curr[1];
		close(curr[1]);
	}
}

void	execute_pipeline(t_data *cmd_list, t_env *env)
{
	pid_t	pid;
	t_file	*rfile;
	t_data	*cmd;
	int		prev_pipe[2];
	int		curr_pipe[2];

	rfile = cmd_list->files;
	cmd = cmd_list;
	prev_pipe[0] = -1;
	prev_pipe[1] = -1;
	while (cmd)
	{
		if (cmd->next && pipe(curr_pipe) == -1)
			err("pipe");
		pid = fork();
		if (pid == -1)
			err("fork");
		if (pid == 0)
			child_proc(cmd, prev_pipe, curr_pipe, env, rfile);
		else
		{
			waitpid(pid, &cmd_list->status, 0);
			parent_proc(prev_pipe, curr_pipe, cmd);
		}
		cmd = cmd->next;
	}
}