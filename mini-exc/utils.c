#include "minishell.h"

void    free_things(char *one, char **two, char *msg, int check)
{
    if(check == 1)
    {
        struc()->index = 0;
        while(two[struc()->index])
        {
            free(two[struc()->index]);
            struc()->index++;
        }
        free(two);
    }
    else if(check == 2)
    {
        struc()->index = 0;
        perror(msg);
        while(two[struc()->index])
        {
            free(two[struc()->index]);
            struc()->index++;
        }
        free(two);
        free(one);
    }
    else
        perror(msg);
    exit(1);
}