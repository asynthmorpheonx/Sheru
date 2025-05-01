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
#include <stdbool.h>
#include <fcntl.h>

extern char **environ;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

# define APPEND 3
# define TRUNC 2
typedef struct s_export
{
	bool			export_check;
	const char		*export_appe;
	char			*export_var;
	char			*export_value;
	struct s_export	*next;
} 					t_export;


typedef struct s_file
{
    char	**infile;
    char	**outfile;
    int		*tid;
}	t_file;

typedef struct s_data
{
	int				status; // check if needed
	int				fds[2];
	char			oldpwd[1024];
	char			pwd[1024];
    char			**cmd;
    char			**data;
    t_file			*files;
	t_export		*export_data;
	struct s_data	*next;
}	t_data;

typedef struct s_env {
	char        *key;           // Variable name (e.g., "PATH")
	char        *value;         // Variable value (e.g., "/usr/bin:/bin")
	struct s_env   *next;       // Pointer to next node
}	t_env;

// typedef struct s_cmd
// {
// 	t_cd 		*cd_data;
// 	t_echo		*echo_data;
// 	t_export 	*export_data;
// 	bool		eflag_check;
// 	int			code;
//     char        *cmd;       // Command name (e.g., "ls", "echo")
//     char        **cmd_flag;
// 	char		*var;
// 	char		*value;  // Arguments (e.g., "-la", "hello")
// 	int         infd;       // Input file descriptor (default: STDIN_FILENO)
//     int         outfd;      // Output file descriptor (default: STDOUT_FILENO)
//     struct s_cmd *next;     // Next command in pipeline/list
// } t_cmd;



// typedef struct s_var // maight delete later(j cole hhhhh)
// {
// 	int prev_pipe[2];
//     int next_pipe[2];		
// 	pid_t pid;
// 	int pip_n;
// 	char *cmd_path;
// 	char	*path;
// 	char	*path_copy;
// 	char	**dir;
// 	char    **cmd_buff;
// 	char	*full_path;
// 	int		index;
// 	int		status;
// }	t_var;


//------- functions after restructuring----
int		builtin_check(char *cmd);
void	check_cmd(t_data *data, t_env *env, int fd);
int 	execute_commands(t_data *data, t_env *env);
void	execute_pipeline(t_data *cmd_list, t_env *env);
char 	*ft_free_array(char **arr);
int 	count_words(char *flags);
int 	envcount(t_env *current);
void    catcpy(char *tmp, char *str, t_env *current);
char    **env_to_array(t_env *env);
char	*ft_cat(char *path, char *cmd);
char	*get_path(char *cmd);
void 	err(char *str);
void	redirect(t_file *files);

// ######### BUILTINs ###############################################
void	ft_cd(t_data *data, t_env *env);
char	*get_home(t_env *env);

void	set_env_var(t_env **env, const char *key, const char *value);
void	sort_tenv(char **env);

void	ft_export(t_data *cmd, t_env *env);
void	ft_var_append(t_env *env, char *var, char *appe);
void	export_print(t_env *env);
char	*ft_envcat(char *dest, const char *src);

void	ft_unset(t_data *data, t_env **env);

void	ft_exit(t_data *data);

void	git_dollar(char *str, t_env *env);
void	ft_echo(t_data *data, t_env *env);
void	echo_print(char *str);

void	ft_env(t_env *env);

void	ft_pwd(void);

#endif
