/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/29 15:51:58 by mel-mouh         ###   ########.fr       */
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

# define AMBIGUOUS_REDIRECT -1
# define RESET 0
# define SET 1

# define USR "USER"
# define SESSIO "SESSION_MANAGER"
# define WD "PWD"

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
	int		herdoc;
}	t_utils;

typedef struct s_files
{
	char			**infile;
	int				*i_type;
	char			**outfile;
	int				*o_type;
}	t_files;

typedef struct s_envp
{
	char			*key;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef	struct s_data
{
	char			**cmd;
	t_files			file;
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

t_envp	*last_env(t_envp *lst);
void	add_to_envp(t_envp **lst, t_envp *tmp);
void	make_env(char **env, t_envp **lst, int i, int j);

t_data	**box(void);
void	ult_exit(void);
t_envp	**envp(void);
t_utils	*util(void);

int		whichtoken(char *input, int *i);
int		token_value(char *input);
bool	token_count(char *str);
void	fill_with_token(char **buffer, int token_id);
char	*buffer_filler(char *s, int *i);
char	**spliting_based_token(char *line);
bool	tokenize(void);

void	stor_redirections(int *arr, char **strs, t_files *file);
void	make_a_file(int incount, int outcount, t_files *file);
void	count_in_out(int *in, int *out, int *arr, char **strs);
void	handle_redirections(int *arr, char **strs, t_files *file, int *mode);

t_data	*last_node(t_data *lst);
void	store_in_tdata(t_data **node, t_data *tmp);
bool	stor_in_list(char **strs, int *arr, t_data **node);

int		cmd_count(char **strs, int *arr);
void	cmd_filler(char **strs, int *arr, char **buffer);
void	cmd_flag_handle(char **strs, int *arr, t_data *node, int *mode);

char	*key_value(char *key);
int		key_len(char *str, int pos);

bool	**ambiguous_ptr(void);

void	remove_quote(char *str, bool *mask, int len);
void	handle_quote(void);

bool	is_ifs(int c);
char	**ifs_split(char const *s);

#endif