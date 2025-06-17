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

bool	odup(t_file *ptr)
{
	int	i;
	int	fd;

	i = 0;
	while (ptr->outfile[i])
	{
		if (ptr->o_type[i] == APP || ptr->o_type[i] == OUD)
		{
			if (ptr->o_type[i] == OUD)
				fd = open(ptr->outfile[i], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(ptr->outfile[i], O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
				return (err(ptr->outfile[i], 3, 0), 0);
			dup2(fd, 1);
			close(fd);
		}
		else if (ptr->o_type[i] == -1)
			return (err(ptr->outfile[i], 4, 0), 0);
		i++;
	}
	return (true);
}

bool	idup(t_file *ptr)
{
	int	i;
	int	fd; // consider adding the fd to a struct 

	i = 0;
	fd = -1;
	while (ptr->infile[i])
	{
		if (ptr->i_type[i] == IND)
		{
			fd = open(ptr->infile[i], O_RDONLY);
			if (fd == -1)
				return (err(ptr->infile[i], 3, 0), 0);
			dup2(fd, 0);
			close(fd);
		}
		else if (ptr->i_type[i] == HERDOC && !ptr->infile[i + 1])
		{
			fd = ft_atoi(ptr->infile[i]);
			dup2(fd, 0);
			close(fd);
		}
		else if (ptr->i_type[i] == -1)
			return (err(ptr->infile[i], 4, 0), 0);
		i++;
	}
	return (true);
}

bool	redirect(t_data *cmd)
{
	if (cmd->file.infile && !idup(&cmd->file))
		return (false);
	if (cmd->file.outfile && !odup(&cmd->file))
		return (false);
	return (true);
}

void err(char *str, int error_status, bool ex_it)
{
	if (error_status == 4)
		ft_putstr_fd("sheru: ", 2);
	if (error_status != 3)
		ft_putstr_fd(str, 2);
	if (error_status == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (error_status == 2)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (error_status == 3)
		perror(str);
	else if (error_status == 4)
		ft_putstr_fd(": ambiguous redirect\n", 2);
	else if (error_status == 127)
		ft_putstr_fd(": command not found\n", 2);
	else if (error_status == 126)
		ft_putstr_fd(": permission denied\n", 2);
	clear_container();
	if (ex_it)
		exit(EXIT_FAILURE);
}
