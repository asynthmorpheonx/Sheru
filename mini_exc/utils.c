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


void	odup(t_file *ptr)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (ptr->outfile[i])
	{
		if (ptr->o_type[i] == APP || ptr->o_type[i] == OUD)
		{
			if (ptr->o_type[i] == OUD)
				fd = open(ptr->outfile[i], O_CREAT | O_TRUNC, 0644);
			else
				fd = open(ptr->outfile[i], O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				// err();
			dup2(fd, 0);
			close(fd);
		}
		else if (ptr->i_type[i] == -1)
			// err();
		i++;
	}
}

void	idup(t_file *ptr)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (ptr->infile[i])
	{
		if (ptr->i_type[i] == IND)
		{
			fd = open(ptr->infile[i], O_RDONLY);
			// if (fd == -1)
				// err();
			dup2(fd, 0);
			close(fd);
		}
		else if (ptr->i_type[i] == HERDOC && !ptr->infile[i + 1])
		{
			fd = ft_atoi(ptr->infile[i]);
			dup2(fd, 0);
			close(fd);
		}
		// else if (ptr->i_type[i] == -1)
			// err();
		i++;
	}
}

void	redirect(t_data *cmd, bool mode)
{
	if (mode)
	{
		offs()->in_backup = dup(0);
		offs()->out_backup = dup(1);
	}
	if (cmd->file.infile)
		idup(&cmd->file);
	if (cmd->file.outfile)
		odup(&cmd->file);

}

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