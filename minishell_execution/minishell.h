#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft/libft.h"

extern char **environ;

typedef struct s_path
{
	char	*path;
	char	*path_copy;
	char	**dir;
	char	*full_path;
	int		index;
}	t_path;

char *get_command_path(char *command);
void    check(char *cmd);

#endif
