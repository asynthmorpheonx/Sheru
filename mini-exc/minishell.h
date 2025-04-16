#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <sched.h>

extern char **environ;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

typedef struct s_cmd
{
    char        *cmd;       // Command name (e.g., "ls", "echo")
    char        *cmd_flag;  // Arguments (e.g., "-la", "hello")
    int         infd;       // Input file descriptor (default: STDIN_FILENO)
    int         outfd;      // Output file descriptor (default: STDOUT_FILENO)
    struct s_cmd *next;     // Next command in pipeline/list
} t_cmd;

typedef struct s_env {
    char        *key;           // Variable name (e.g., "PATH")
    char        *value;         // Variable value (e.g., "/usr/bin:/bin")
    struct s_env   *next;       // Pointer to next node
} t_env;

typedef struct s_var
{
	int prev_pipe[2];
    int next_pipe[2];		
	pid_t pid;
	int pip_n;
	char *cmd_path;
	char	*path;
	char	*path_copy;
	char	**dir;
	char    **cmd_buff;
	char	*full_path;
	int		index;
}	t_var;

char *get_command_path(char *cmd);
void    check(char *commands);
char *pat(char *cmd);
t_var  *struc(void);
void    whitespace_trim(t_var *s);
void    setup_redirection(t_var *s);
void    parent_cleanup(t_var *s);
void    execute_pipe_sequence(t_var *s);
void    execute_single_command(t_var *s);

#endif
