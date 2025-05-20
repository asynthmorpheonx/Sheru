#include "mini_shell.h"

t_offs *offs(void)
{
	static t_offs x;

	return (&x);
}

void	sort_tenv(char **env)
{
	char	*tmp;
	
	int (i), (u);
	i = 0;
	while (env[i])
	{
		u = i + 1;
		while(env[u])
		{
			if (ft_strcmp(env[u], env[i]) < 0)
			{
				tmp = env[u];
				env[u] = env[i];
				env[i] = tmp; 
			}
			u++;
		}
		i++;
	}
}

void	odup(char *file, int type, int is_input, int *fd)
{
	if (is_input)
		*fd = open(file, O_RDONLY);
	else if (type == 2)
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd == -1)
		perror("open");
	if(is_input)
	{
		dup2(*fd, STDIN_FILENO);
		offs()->redir = 2;
	}
	else
	{
		dup2(*fd, STDOUT_FILENO);
		offs()->redir = 1;
	}
	close(*fd);
}

void	redirect(t_data *cmd)
{
	int	(index);

	index = 0;
	while (cmd->file.infile && cmd->file.infile[index])
	{
		odup(cmd->file.infile[index], 0, 1, &offs()->redirected_fd);
		index++;
	}
	index = 0;
	while (cmd->file.outfile && cmd->file.outfile[index])
	{
		odup(cmd->file.outfile[index], cmd->file.o_type[index], 0, &offs()->redirected_fd);
		index++;
	}
}

void err(char *str) //check if a function like this already exist
{
	//free memory
	if(str)
		// call the garbage colecctor whenevr it's setted up
	perror(str);
	exit(EXIT_FAILURE);
}