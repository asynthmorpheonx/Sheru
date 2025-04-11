#include "minishell.h"
// #include "libft/libft.h"
// #include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void    ft_free()
{
    int i = 0;
    while (pth()->dir[i])
    {
        free(pth()->dir[i]);
        i++;
    }
    free(pth()->dir);
    //free(pth()->path_copy);
}

void    check(char **commands, int pips)
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
        //perror("execve failed");
        //exit(1);
    }
    if (i > 0)
    {
        
        free(full_path);
        ft_free();
        // exit(1);
    }
    else {
        free(full_path);
        ft_putstr_fd("Command not found: ", 2);
        ft_putendl_fd(cmd, 2);
        // exit(1);
    }
}

int main(int ac, char **av, char **env)
{
    if(ac == 1)
    {
		int i = 0;
		char **cmds;
        while ("true")
        {
            printf("minishell: ");
            char* line = readline(0);
            cmds = ft_split(commands, ' ');
			if(ac - 1 > 1)
			{
				while()
				check(cmds);		
			}
            free(line);
        }
    }
}