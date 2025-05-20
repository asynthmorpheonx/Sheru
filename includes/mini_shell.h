/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/20 15:38:12 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <libft.h>
# include <ft_printf.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <heap_controller.h>
# include <stdbool.h>
# include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

# define AMBIGUOUS_REDIRECT -1
# define RESET 0
# define SET 1

# define USR "USER"
# define OS "DESKTOP_SESSION"
# define SESSIO "SESSION_MANAGER"

typedef struct s_quote
{
	char	**strs;
	bool	**bitmaks;
}	t_quote;

typedef enum e_token
{
	IND,
	OUD,
	APP,
	PIPE,
	HERDOC,
	WORD
}	t_token;

typedef struct s_export
{
	bool			export_check;
	const char		*export_appe;
	char			*export_var;
	char			*export_value;
	// struct s_export	*next;
} 					t_export;

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

typedef struct s_ferror
{
	bool	flage;
	bool	full_exp;
	bool	error;
}	t_ferror;

typedef struct s_utils
{
	char	**s;
	int		*a;
	int		t;
}	t_utils;

typedef struct s_file
{
	char			**infile;
	int				*i_type;
	char			**outfile;
	int				*o_type;
}	t_file;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_env;

typedef	struct s_data
{
	char			**cmd;
	t_file			file;
	t_export		*export_data;
	struct s_data	*next;
}	t_data;

void	begin_lexing(char *line);
int		whichtoken(char *input, int *i);
int		ft_iswhitespace(int c);
int		ft_ispecial(int c);
int		skip_quots(char *line, int *i);
bool	token_count(char *str);
void	fill_with_token(char **buffer, int token_id);
char	*safe_substr(char *str, unsigned int start, size_t len);
char	*buffer_filler(char *line, int *i);
char	**spliting_based_token(char *line);

t_env	*last_env(t_env *lst);
void	add_to_envp(t_env **lst, t_env *tmp);
void	make_env(char **env, t_env **lst, int i, int j);

size_t	size_quot(char *str);
void	remove_quote(size_t len, char **str, int i, int j);
void	handle_quote(void);
int		skip_quots(char *line, int *i);

t_data	**box(void);
void	ult_exit(void);
t_env	**envp(void);
t_utils	*util(void);

int		whichtoken(char *input, int *i);
int		token_value(char *input);
bool	token_count(char *str);
void	fill_with_token(char **buffer, int token_id);
char	*buffer_filler(char *s, int *i);
char	**spliting_based_token(char *line);
bool	tokenize(void);

void	stor_redirections(int *arr, char **strs, t_file *file);
void	make_a_file(int incount, int outcount, t_file *file);
void	count_in_out(int *in, int *out, int *arr, char **strs);
void	handle_redirections(int *arr, char **strs, t_file *file, int *mode);

t_data	*last_node(t_data *lst);
void	store_in_tdata(t_data **node, t_data *tmp);
bool	stor_in_list(char **strs, int *arr, t_data **node);

int		cmd_count(char **strs, int *arr);
void	cmd_filler(char **strs, int *arr, char **buffer);
void	cmd_flag_handle(char **strs, int *arr, t_data *node, int *mode);

char	*key_value(char *key);
int		key_len(char *str, int pos);

bool	**ambiguous_ptr(void);

bool	is_ifs(int c);
char	**ifs_split(char const *s);

int		builtin_check(char *cmd);
void 	execute_commands(t_data *data, t_env *env);
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