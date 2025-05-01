#include "minishell.h"

// void    free_things(char *one, char **two, char *msg, int check) // maight delet later
// {
//     if(check == 1)
//     {
//         struc()->index = 0;
//         while(two[struc()->index])
//         {
//             free(two[struc()->index]);
//             struc()->index++;
//         }
//         free(two);
//     }
//     else if(check == 2)
//     {
//         struc()->index = 0;
//         perror(msg);
//         while(two[struc()->index])
//         {
//             free(two[struc()->index]);
//             struc()->index++;
//         }
//         free(two);
//         free(one);
//     }
//     else
//         perror(msg);
//     exit(1);
// }

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

void odup(char *file, int id, int check)
{
	int fd;

	if(!check)
	{
		if(id == 3)
			fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			perror("open outfile");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else 
	{
		fd = open(file, O_CREAT | O_RDONLY);
		if(fd == -1)
		perror("open infile");;
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

char	*inorout(t_file *files, char *last_in, char *last_out, int *i)
{
	int	index;

	index = 0;
	while(files->infile[index])
	{
		if(files->infile[index])
			*last_in = files->infile[index];
		index++;
	}
	index = 0;
	while(files->outfile[index])
	{
		if(files->outfile[index])
			*last_in = files->outfile[index];
		if(files->tid[index])
			*i = files->tid[index];
		index++;
	}
}
void	redirect(t_file *files) // (> , < are handled but i need to edit on he code(struct) to handle >> )
{
	int	i;

	char *(last_in), *(last_o);
	last_in = NULL;
	last_o = NULL;
	inorout(files, last_in, last_o, &i);
	if(last_o)
		odup(last_o, i, 0);
	if(last_in)
		odup(last_in, i, 1);
}

void err(char *str) //check if a function like this already exist
{
	//free memory
	if(str)
		// call the garbage colecctor whenevr it's setted up
	perror(str);
	exit(EXIT_FAILURE);
}