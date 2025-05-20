#include "mini_shell.h"

//#############
//
//fds = [0][1] : [0] to read frpm | [1] to write into
//
//#############
void close_fds(int *fds)
{
	if (fds[0] != -1)
		close(fds[0]);
	if (fds[1] != -1)
		close(fds[1]);
}

void ft_exec(t_data *cmd, t_env *env)
{
	if (offs()->prev_fds[0] != -1)
	{
		dup2(offs()->prev_fds[0], STDIN_FILENO);
		close_fds(offs()->prev_fds);
	}
	if (cmd->next)
	{
		dup2(offs()->curr_fds[1], STDOUT_FILENO);
		close(offs()->curr_fds[1]);
	}
	execve(get_path(cmd->cmd[0]), cmd->cmd, env_to_array(env));
	err("execve");
}

void child_proc(t_data *cmd, t_env *env)
{
	 // performs dup2 for in/out file
	if (cmd->file.infile || cmd->file.outfile)
		redirect(cmd);
	if (builtin_check(cmd->cmd[0]) && cmd->next) // run builtin in child if it's part of a pipeline
	{
		// Temporarily redirect stdout to pipe
		dup2(offs()->curr_fds[1], STDOUT_FILENO);
		ft_ceue(cmd, env);
		dup2(offs()->out_backup, STDOUT_FILENO);
		close(offs()->curr_fds[1]);
		exit(EXIT_SUCCESS);
	}
	else if (builtin_check(cmd->cmd[0]))
	{
		ft_ceue(cmd, env);
		exit(EXIT_SUCCESS); // prevent falling through
	}
	else
		ft_exec(cmd, env);
}

void parent_proc(t_data *cmd)
{
	close_fds(offs()->prev_fds);

	if (cmd->next) // Always pass pipe fd to next command
	{
		offs()->prev_fds[0] = offs()->curr_fds[0];
		offs()->prev_fds[1] = offs()->curr_fds[1];
		close(offs()->curr_fds[1]);
	}
	else
		close_fds(offs()->curr_fds);
}

void execute_pipeline(t_data *cmd, t_env *env)
{
	pid_t pid;
	int	status;

	offs()->prev_fds[0] = -1;
	offs()->prev_fds[1] = -1;
    offs()->curr_fds[0] = -1;
    offs()->curr_fds[1] = -1;
	if (cmd->next && pipe(offs()->curr_fds) == -1)
		err("pipe");
	pid = fork();
	if (pid == -1)
		err("fork");
	if (pid == 0)
		child_proc(cmd, env);
	else
	{
		waitpid(pid, &status, 0);
		parent_proc(cmd);
	}
}

