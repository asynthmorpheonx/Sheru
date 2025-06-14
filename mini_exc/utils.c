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

// void	indir_dup(t_data *box)
// {
// 	int	i;
// 	int redirected_fd;

// 	i = 0;
// 	while (box->file.infile && box->file.infile[i])
// 	{
// 		if (box->file.i_type[i] == HERDOC && !box->file.infile[i + 1])
// 		{
// 			printf("=====> %s\n", box->file.infile[i]);
// 			redirected_fd = ft_atoi(box->file.infile[i]);
// 		}
// 		else if (box->file.i_type[i] == -1)
// 		{	
// 			printf("1\n");
// 			err(box->file.infile[i], 4);}
// 		else
// 		{
// 			redirected_fd = open(box->file.infile[i], O_RDONLY);
// 			if (redirected_fd == -1)
// 			{	
// 				printf("2\n");
// 				err(box->file.infile[i], 3);}
// 		}
// 		dup2(redirected_fd, STDIN_FILENO);
// 		close(redirected_fd);
// 		i++;
// 	}
// }

// void	outdir_dup(t_data *box)
// {
// 	int	i;
// 	int redirected_fd;

// 	i = 0;
// 	while (box->file.outfile && box->file.outfile[i])
// 	{
// 		if (box->file.o_type[i] == APP && !box->file.outfile[i])
// 		{
// 			redirected_fd = open(box->file.outfile[i], O_CREAT | O_APPEND, 0644);
// 			if (redirected_fd == -1)
// 			{
// 				printf("3\n");
// 				err(box->file.outfile[i], 3);}
// 		}
// 		else if (box->file.o_type[i] == -1)
// 			err(box->file.outfile[i], 4);
// 		else
// 		{
// 			redirected_fd = open(box->file.outfile[i], O_TRUNC, 0644);
// 			if (redirected_fd == -1)
// 			{	
// 				printf("4\n");}
// 				// err(box->file.outfile[i], 3);}
// 		}
// 		dup2(redirected_fd, STDOUT_FILENO);
// 		close(redirected_fd);
// 		i++;
// 	}
// }

// void	redirect(t_data *cmd)
// {
// 	if(cmd->file.infile)
// 		indir_dup(cmd);
// 	if(cmd->file.outfile)
// 		outdir_dup(cmd);
// }


void	odup(char *file, int type, int is_input, int *fd)
{
	if (is_input)
		*fd = open(file, O_RDONLY);
	else if(type == HERDOC && file + 1)
		*fd = ft_atoi(file);
	else if (type == 2)
		*fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		*fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd == -1)
		perror("open");
	if (is_input)
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


// void	redirect(t_data *cmd)
// {
// 	int	(index);

// 	index = 0;
// 	while (cmd->file.infile && cmd->file.infile[index])
// 	{
// 		odup(cmd->file.infile[index], 0, 1, &offs()->redirected_fd);
// 		index++;
// 	}
// 	index = 0;
// 	while (cmd->file.outfile && cmd->file.outfile[index])
// 	{
// 		odup(cmd->file.outfile[index], cmd->file.o_type[index], 0, &offs()->redirected_fd);
// 		index++;
// 	}
// }


void err(char *str, int error_status) //check if a function like this already exist
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
	clear_container();
	exit(EXIT_FAILURE);
}