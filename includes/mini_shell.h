/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/19 23:35:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <heap_controller.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
#include <sys/ioctl.h>
#include <fcntl.h>

typedef char t_prstat;

# define AMBIGUOUS_REDIRECT -1
# define RESET 0
# define SET 1
# define USR "USER"
# define SESSIO "SESSION_MANAGER"
# define WD "PWD"
# define SCANIN 0b1001010
# define HERDOC_READ 0b1011001
# define INTERRUPTED 0b1110010
# define EAPP 0b00000010
# define ESET 0b00000001
# define ENOT 0b00000000


typedef struct s_exutil
{
	int		c_count;
	int		ind;
	bool	is_builtin;
}	t_exutil;


typedef struct s_exp
{
	char	**du;
	char	**extend;
	int		*tokn;
	bool	**mask;
	int		len;
	int		i;
	int		j;
}	t_exp;

typedef struct s_quoter
{
	char	*s;
	bool	*m;
	int		fap;
	int		sap;
}	t_quoter;

typedef enum e_token
{
	IND,
	OUD,
	APP,
	PIPE,
	HERDOC,
	WORD
}	t_token;

typedef struct s_offs
{
	int		in_backup;
	int		out_backup;
	char	pwd[4096];
	int		**pipes;
	pid_t	*pids;
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
	bool	**mask;
	int		*a;
	int		t;
	int		ports[16];
	int		herdoc;
	bool	herdoc_exp;
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
void	ult_exit(void);

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

int		cmd_count(char **strs, int *arr, int i);
void	cmd_filler(char **strs, int *arr, char **buffer, int i);
void	cmd_flag_handle(char **strs, int *arr, t_data *node, int i);

char	*key_value(char *key);
int		key_len(char *str, int pos);


void	remove_quote(char *str, bool *mask, int len);
void	handle_quote(void);

bool	is_ifs(int c);
char	**ifs_split(char const *s);

int			builtin_check(char *cmd);
void 		ft_free_array(char **arr);
int 		envcount(t_env *env);
void   		catcpy(char *tmp, t_env *current);
char		*get_path(char *cmd, int *error_status);
t_offs		*offs(void);
void		ft_ceue(t_data *data, t_env **env);
void		ft_cd(t_data *cmd);
void		sort_tenv(char **env);
void		export_print(t_env **env);
void		ft_unset(t_data *data, t_env **env);
void		ft_exit(void);
void		ft_echo(t_data *data);
void		ft_env(t_env **env);
void		ft_pwd(void);
void		code_setter(int	new_code);

char	*ft_keydup(const char *s1);

void		fetch_setter(bool mode, int i, bool is_full);
char		*creat_prompt(void);
void		expansion_data(int i, int j, int to, int sto);
bool		*mask_joining(bool *o_mask, char *pre, char *suff);
bool		creat_mask(void);
char		*safe_join(char *s1, char *s2);
int			lenght_both(char **s1, char **s2);
bool		*handle_masking(char *str, int start, int len);
bool		*mask_joining(bool *o_mask, char *pre, char *suff);
int			node_count(void);
void		execute_command(t_data *cmd);

void	close_pipes(int **pipes);
int		execute_pipeline(t_data *cmd);
bool	redirect(t_data *cmd);
void	err(char *str, int error_status, bool ex_it);

t_exutil	*executer(void);
void		wait_for_childs(void);
bool		safer_fork(pid_t process_id, int ind, t_data *cmd);
void		handle_pipes(t_data *cmd, int ind);
void		make_pids(int ccount);
void		child_exec(t_data *cmd);
void		close_herdoc_ports(void);

void	ft_export(t_data *cmd);
char	*exit_code(void);
char	*path_join(char *path, char *cmd);

char    **env_to_array(t_env *ptr);

t_data **box(void);
t_prstat	*process_status(void);
t_env **envp(void);
t_ferror *fetcher(void);
t_utils *util(void);


#endif