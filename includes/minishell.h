/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/19 15:34:37 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <libft.h> 
# include <ft_printf.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <heap_controller.h>
# include <sched.h>
# include <stdbool.h>
# include <fcntl.h>
#include <sys/wait.h>

extern char **environ;

#define STDIN_FILENO 0
#define STDOUT_FILENO 1

typedef enum e_token
{
	PIPE,
	IND,
	OUD,
	APP,
	HERDOC,
	WORD,
}	t_token;

# define APPEND APP
# define TRUNC OUD

typedef struct s_utils
{
	char	**s;
	int		*a;
	int		t;
}	t_utils;

typedef struct s_export
{
	bool			export_check;
	const char		*export_appe;
	char			*export_var;
	char			*export_value;
	// struct s_export	*next;
} 					t_export;

typedef struct s_files
{
    char	**infile;
    char	**outfile;
    int		*o_type;
}	t_files;

typedef struct s_offs
{
	bool			redirection;
	int 			check;
	int				redir;
	int				in_backup;
	int				out_backup;
	int				prev_fds[2];
	int 			curr_fds[2];
	char			oldpwd[1024];
	char			pwd[1024];
	int				redirected_fd;
}	t_offs;


typedef struct s_data
{
	int				status; // check if needed
    char			**cmd;
    t_files			files;
	t_export		*export_data;
	struct s_data	*next;
}	t_data;

typedef struct s_env {
	char        *key;           // Variable name (e.g., "PATH")
	char        *value;         // Variable value (e.g., "/usr/bin:/bin")
	struct s_env   *next;       // Pointer to next node
}	t_env;

//################### PARSING FUNCTIONS ##################################3

void	begin_lexing(char *line, char **env);
int		whichtoken(char *input, int *i);
int		ft_iswhitespace(int c);
int		ft_ispecial(int c);
int		skip_quots(char *line, int *i);
int		token_count(char *str);
void	fill_with_token(char **buffer, int token_id);
char	*safe_substr(char *str, unsigned int start, size_t len);
char	*handle_quote(char *line, int *i, int *mode);
char	*buffer_filler(char *line, int *i, int *mode);
char	**spliting_based_token(char *line);

//#################### EXECUTION PART ######################################

int		builtin_check(char *cmd);
void 	execute_commands(t_data *data, char **env);
void	execute_pipeline(t_data *cmd, t_env *env);
char	*ft_free_array(char **arr);
int 	count_words(char *flags);
int 	envcount(t_env *current);
void    catcpy(char *tmp, char *str, t_env *current);
char    **env_to_array(t_env *env);
char	*ft_cat(char *path, char *cmd);
char	*get_path(char *cmd);
void 	err(char *str);
void	redirect(t_data *cmd);
char 	*word(char *str);
t_offs	*offs(void);
void	ft_ceue(t_data *data, t_env *env);


// ######### BUILTINs ###############################################
void	ft_cd(t_data *data, t_env *env);
char	*get_home(t_env *env);

void	set_env_var(t_env **env, const char *key, const char *value);
void	sort_tenv(char **env);

void	ft_export(t_data *cmd, t_env **env);
void	ft_var_append(t_env *env, char *var, const char *appe);
void	export_print(t_env *env);
char	*ft_envcat(char *dest, const char *src);
void	build_export_data(t_data *cmd_list, char *container);

void	ft_unset(t_data *data, t_env **env);

void	ft_exit(t_data *data);

void	git_dollar(char *str, t_env *env);
void	ft_echo(t_data *data, t_env *env);
void	echo_print(char *str);

void	ft_env(t_env *env);

void	ft_pwd(void);

#endif
