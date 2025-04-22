/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/22 23:31:06 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

//it return the token id of the the char that we are dealing with
//it increament the value of 'i' in some cases
int	whichtoken(char *input, int *i)
{
	if (!ft_strncmp(input + *i, "<<", 2))
	{
		(*i) += 1;
		return(HERDOC);
	}
	else if (!ft_strncmp(input + *i, ">>", 2))
	{
		(*i) += 1;
		return (APPEND);	
	}	
	else if (input[*i] == '|')
		return (PIPE);
	else if (input[*i] == '<')
		return (INDIRECT);
	else if (input[*i] == '>')
		return (OUDIRECT);
	else
		return (WORD);
}

//checks the bytes if it's an white space
int	ft_iswhitespace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

//check the bytes if it's an a an special character
int	ft_ispecial(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	skip_quots(char *line, int *i)
{
	int	j;
	int	toggle;

	toggle = 1;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (toggle == 1)
			{
				j = (*i);
				toggle = 0;
			}
			else if (line[*i] == line[j])
				toggle = 1;
		}
		else if (ft_iswhitespace(line[*i]) && toggle == 1)
			break ;
		(*i)++;
	}
	if (toggle)
		return (1);
	return (0);
}

//count token in the string
int token_count(char *str)
{
	int	i;
	int	tcount;

	i = 0;
	tcount = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if ((str[i] == '>' || str[i] == '<')
			&& (str[i + 1] == '>' || str[i + 1] == '<'))
			i += 2;
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i++;
		else if (str[i] == '"' || str[i] == '\'')
		{
			if (!skip_quots(str, &i))
				return (-1);
		}
		else
		{
			while (str[i] && !ft_iswhitespace(str[i])
				&& str[i] != '|' && str[i] != '>' && str[i] != '<')
					i++;
		}
		tcount++;
	}
	return (tcount);
}

void	fill_with_token(char **buffer, int token_id)
{
	if (token_id == PIPE)
		*buffer = ft_strdup("|");
	else if (token_id == INDIRECT)
		*buffer = ft_strdup("<");
	else if (token_id == OUDIRECT)
		*buffer = ft_strdup(">");
	else if (token_id == APPEND)
		*buffer = ft_strdup(">>");
	else if (token_id == HERDOC)
		*buffer = ft_strdup("<<");
	g_lst_addback(g_new_garbage(*buffer));
}

char	*safe_substr(char *str, unsigned int start, size_t len)
{
	char	*pp;

	printf("substr  the len is: %zu\n", len);
	pp = ft_substr(str, start, len);
	if (!pp)
		return (NULL);
	g_lst_addback(g_new_garbage(pp));
	return (pp);
}

char	*handle_quote(char *line, int *i, int *mode)
{
	int	j;
	int	k;

	j = *i;
	k = 0;
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == line[j])
		{
			(*i)++;
			return (safe_substr(line, j + 1, k));
		}
		else
			k++;
		(*i)++;
	}
	*mode = -1;
	return (NULL);
}

char	*buffer_filler(char *line, int *i, int *mode)
{
	int	j;
	char	*str;

	str = NULL;
	while (ft_iswhitespace(line[*i]))
		(*i)++;
	while (line[*i])
	{
		if (ft_iswhitespace(line[*i]) || ft_ispecial(line[*i]))
			break ;
		else if (line[*i] == '\'' || line[*i] == '"')
			str = ft_gnl_strjoin(str, handle_quote(line, i, mode));
		else
		{
			j = *i;
			while (line[*i] && line[*i] != '\'' && line[*i] != '"'
				&& !ft_iswhitespace(line[*i]) && !ft_ispecial(line[*i]))
				(*i)++;
			str = ft_gnl_strjoin(str, safe_substr(line, j, *i - j));
		}
	}
	return (str);
}

char	**spliting_based_token(char *line)
{
	int		i;
	int		k;
	int		quote_status;
	char	**strs;

	i = 0;
	k = 0;
	strs = safe_alloc((token_count(line) + 1) * sizeof(char *), 0);
	if (!strs)
		return (NULL);
	while (line[i])
	{
		quote_status = 0;
		while(ft_iswhitespace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			fill_with_token(strs + k, whichtoken(line, &i));
			i++;
		}
		else
		{
			strs[k] = buffer_filler(line, &i, &quote_status);
			if (!strs[k])
				return (NULL);
		}
		k++;
	}
	return (strs);
}

void	begin_lexing(char *line)
{
	char	**strs;
	int		i;

	i = 0;
	printf("====[%d]====\n",token_count(line));
	if (token_count(line) < 0)
	{
		printf("non end quots\n");
		return ;
	}
	strs = spliting_based_token(line);
	while (strs[i])
	{
		printf("line %d:[%s]\n",i, strs[i]);
		i++;
	}
}

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("sheru>");
		if (!line)
			return (clear_container(), 0);
		add_history(line);
		begin_lexing(line);
	}
	return (0);
}
