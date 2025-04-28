/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/28 01:46:04 by mel-mouh         ###   ########.fr       */
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
	char	*infile;
	char	*outfile;
	int		o_type;
}	t_files;

typedef	struct s_data
{
	char			**cmd;
	char			**data;
	bool			isbuilt_in;
	t_files			file;
	struct s_data	*next;
}	t_data;

void	begin_lexing(char *line);
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


#endif