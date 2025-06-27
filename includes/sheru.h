/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sheru.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:25:22 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHERU_H
# define SHERU_H

# include <libft.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <heap_controller.h>
# include <stdbool.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/stat.h>

typedef char	t_prstat;

# define AMBIGUOUS_REDIRECT -1
# define RESET 0
# define SET 1
# define USR "USER"
# define SESSIO "SESSION_MANAGER"
# define WD "PWD"
# define SCANIN 0b1001010
# define HERDOC_READ 0b1011001
# define INTERRUPTED 0b1110010
# define WAITIN 0b0010011
# define EAPP 0b00000010
# define ESET 0b00000001
# define ENOT 0b00000000

# define DFLPATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

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
	int		fpi[2];
	int		spi[2];
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

typedef struct s_data
{
	char			**cmd;
	t_file			file;
	struct s_data	*next;
}	t_data;

t_env		*last_env(t_env *lst);
t_data		*last_node(t_data *lst);
t_offs		*offs(void);
t_exutil	*executer(void);
t_data		**box(void);
t_prstat	*process_status(void);
t_env		**envp(void);
t_ferror	*fetcher(void);
t_utils		*util(void);
bool		token_count(char *str);
bool		token_count(char *str);
bool		tokenize(void);
bool		stor_in_list(char **strs, int *arr, t_data **node);
bool		is_ifs(int c);
bool		*mask_joining(bool *o_mask, char *pre, char *suff);
bool		creat_mask(void);
bool		*handle_masking(char *str, int start, int len);
bool		*mask_joining(bool *o_mask, char *pre, char *suff);
bool		redirect(t_data *cmd, bool child_pr);
bool		safer_fork(pid_t process_id, int ind, t_data *cmd);
bool		syntax_check(void);
bool		check_value(char *str);
bool		check_operator(char *arg, int *ind, int *mode);
int			whichtoken(char *input, int *i);
int			ft_iswhitespace(int c);
int			ft_ispecial(int c);
int			skip_quots(char *line, int *i);
int			whichtoken(char *input, int *i);
int			token_value(char *input);
int			cmd_count(char **strs, int *arr, int i);
int			key_len(char *str, int pos);
int			builtin_check(char *cmd);
int			envcount(t_env *env);
int			lenght_both(char **s1, char **s2);
int			node_count(void);
int			execute_pipeline(t_data *cmd);
int			join_preffix(int end, t_exp *ptr);
char		*safe_substr(char *str, unsigned int start, size_t len);
char		*buffer_filler(char *line, int *i);
char		**spliting_based_token(char *line);
char		*buffer_filler(char *s, int *i);
char		**spliting_based_token(char *line);
char		*key_value(char *key);
void		remove_quote(char *str, bool *mask, int len);
char		*get_path(char *cmd, int *error_status);
char		*ft_keydup(const char *s1);
char		*creat_prompt(void);
char		*safe_join(char *s1, char *s2);
void		execute_command(t_data *cmd);
char		*exit_code(void);
char		**env_to_array(t_env *ptr);
char		*path_join(char *path, char *cmd, int *status);
char		*path_already(char *cmd, int *status);
char		*get_path(char *cmd, int *error_status);
char		*ft_readline(void);
void		begin_lexing(char *line);
void		fill_with_token(char **buffer, int token_id);
void		add_to_envp(t_env **lst, t_env *tmp);
void		make_env(char **env, t_env **lst, int i, int j);
void		ult_exit(void);
void		fill_with_token(char **buffer, int token_id);
void		stor_redirections(int *arr, char **strs, t_file *file, int i);
void		make_a_file(int incount, int outcount, t_file *file);
void		count_in_out(int *in, int *out, int *arr, char **strs);
void		handle_redirections(int *arr, char **strs, t_file *file, int *mode);
void		store_in_tdata(t_data **node, t_data *tmp);
void		cmd_filler(char **strs, int *arr, char **buffer, int i);
void		cmd_flag_handle(char **strs, int *arr, t_data *node, int i);
void		handle_quote(void);
char		**ifs_split(char const *s);
void		ft_free_array(char **arr);
void		catcpy(char *tmp, t_env *current);
void		ft_ceue(t_data *data, t_env **env);
void		ft_cd(t_data *cmd);
void		sort_tenv(char **env);
void		export_print(t_env **env);
void		ft_unset(t_data *data, t_env **env);
void		ft_exit(t_data *cmd);
void		ft_echo(t_data *data);
void		ft_env(t_env **env);
void		ft_pwd(void);
void		code_setter(int new_code);
void		fetch_setter(bool mode, int i, bool is_full);
void		expansion_data(int i, int j, int to, int sto);
void		close_pipes(void);
void		err(char *str, int error_status, bool ex_it);
void		wait_for_childs(void);
void		handle_pipes(t_data *cmd, int ind);
void		make_pids(int ccount);
void		child_exec(t_data *cmd);
void		close_herdoc_ports(void);
void		ft_export(t_data *cmd);
void		reset_util_box(void);
void		herdoc_job(void);
void		reset_data_box(void);
void		init_shlvl(void);
void		interupt_handle(int sig_num);
void		make_pipe(void);
void		pipe_indexing(void);
void		replace_fd(t_data *node, char *str, int i);
void		here_doc_util(char *input, int fd);
void		safe_pipe(int *fds);
void		close_herdoc_ports(void);
void		expand_herdoc_data(char *str, int fd);
void		handle_if_begin_with_ifs(int start, t_exp *ubox, char *value);
void		extend_key(int *index, int *start, char *value, int end);
void		replace_key_to_value(int *ind, int *strt, int k_len, char *value);
void		expand_value(int *index, int *start);
void		switch_toggles(int *toggle);
void		add_extended(t_exp *ubox);
void		add_suffix(t_exp *ubox);
void		expansion_util(int *ind, t_exp *ubox, int end, int tmp);
void		build_data(char **args);
void		redir_msg_err(int err_num, char *str);

#endif