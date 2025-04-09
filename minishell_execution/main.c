#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>

void    check(char *cmd)
{
    char *full_path = get_command_path(cmd);
    pid_t i = fork();
    if(i < 0)
    {
        printf("pid error\n");
        exit(1);
    }
    if ((i == 0) && full_path) {
        execve(full_path, (char *[]){"ls", NULL}, environ);
        free(full_path);
        perror("execve failed");
        exit(1);
    }
    if(i > 0)
    {
        free(full_path);
        exit(1);
    }
    else {
        free(full_path);
        ft_putendl_fd("Command not found: ls \n", 2);
        exit(1);
    }
}

int main(int ac, char ** av)
{
    if(ac == 2)
    {
        check(av[1]);
    }
}