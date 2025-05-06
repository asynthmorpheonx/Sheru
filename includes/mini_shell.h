/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/06 22:10:53 by mel-mouh         ###   ########.fr       */
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

typedef enum e_token
{
	PIPE,
	IND,
	OUD,
	APP,
	HERDOC,
	WORD
}	t_token;

typedef struct s_utils
{
	char	**s;
	int		*a;
	int		t;
}	t_utils;

typedef struct s_files
{
	char			**infile;
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
	char			**her_doc;
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

int		here_doc_count(int *arr, char **strs);
char	**stor_delimiters(int *arr, char **str, int count);
char	**heredoc_heandler(char **str, int *arr, int *mode);

t_envp	*last_env(t_envp *lst);
void	add_to_envp(t_envp **lst, t_envp *tmp);
void	make_env(char **env, t_envp **lst, int i, int j);

size_t	size_quot(char *str);
void	remove_quote(size_t len, char **str, int i, int j);
void	handle_quote(void);
int	skip_quots(char *line, int *i);

t_data	**box(void);
void	ult_exit(void);
t_envp	**envp(void);
t_utils	*util(void);

int	whichtoken(char *input, int *i);
int	token_value(char *input);
bool token_count(char *str);
void	fill_with_token(char **buffer, int token_id);
char	*buffer_filler(char *s, int *i);
char	**spliting_based_token(char *line);
bool	tokenize(void);


#endif