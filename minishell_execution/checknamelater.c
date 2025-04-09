#include "minishell.h"

t_path  *pth(void)
{
    static t_path x;
    
    return(&x);
}

char *get_command_path(char *command)
{
    pth()->path = getenv("PATH");
    if (!pth()->path)
    {
        ft_putendl_fd("minishell: PATH environment variable not set", 2);
        return NULL;
    }
    pth()->path_copy = ft_strdup(pth()->path);
    if (!pth()->path_copy)
    {
        perror("minishell: strdup failed");
        return NULL;
    }
    pth()->dir = ft_split(pth()->path_copy, ':');
    pth()->full_path = NULL;

    while (pth()->dir[pth()->index ] != NULL)
    {
        pth()->full_path = malloc(ft_strlen(pth()->dir[pth()->index]) + ft_strlen(command) + 2);
        if (!pth()->full_path) {
            perror("minishell: malloc failed");
            free(pth()->path_copy);
            return NULL;
        }
        ft_strcpy(pth()->full_path, pth()->dir[pth()->index]);
        ft_strcat(pth()->full_path, "/");
        ft_strcat(pth()->full_path, command);
        if (access(pth()->full_path, X_OK) == 0) {
            free(pth()->path_copy);
            return (pth()->full_path);  // Caller must free this memory
        }
        free(pth()->full_path);
        pth()->full_path = NULL;
        pth()->index++;
    }
    free(pth()->path_copy);
    return NULL;  // Command not found in PATH
}