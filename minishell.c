/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/17 17:41:09 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

//it return the token id of the the char that we are dealing with
//it increament the value of 'i' in some cases
int	whichtoken(char *input, int *i)
{
	if (!ft_strncmp(input + *i, "<<", 2))
	{
		(*i) += 2;
		return(HERDOC);
	}
	else if (!ft_strncmp(input + *i, ">>", 2))
	{
		(*i) += 2;
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
		if (str[i])
		{
			if ((str[i] == '>' || str[i] == '<')
				&& (str[i + 1] == '>' || str[i + 1] == '<'))
				i += 2;
			else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
				i++;
			else
				while (str[i] && !ft_iswhitespace(str[i])
					&& str[i] != '|' && str[i] != '>' && str[i] != '<')
	                i++;
			tcount++;
		}
	}
	return (tcount);
}

char	*fill_with_token(int token_id)
{
	char	*buffer;

	if (token_id == PIPE)
		buffer = ft_strdup("|");
	else if (token_id == INDIRECT)
		buffer = ft_strdup("<");
	else if (token_id == OUDIRECT)
		buffer = ft_strdup(">");
	else if (token_id == APPEND)
		buffer = ft_strdup(">>");
	else if (token_id == HERDOC)
		buffer = ft_strdup("<<");
	else
		return (NULL);
	g_lst_addback(g_new_garbage(buffer));
	return (buffer);
}

// char	**spliting_based_token(char *line)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		last_tid;
// 	char	**strs;

// 	i = 0;
// 	k = 0;
// 	strs = safe_alloc((extract_token_count(line) + 1) * sizeof(char *), 0);
// 	if (!strs)
// 		return (NULL);
// 	while(line[i])
// 	{
// 		while (ft_iswhitespace(line[i]))
// 			i++;
// 		last_tid = whichtoken(line, &i);
// 		if (line[i])
// 		{
// 			j = i;
// 			if (last_tid == WORD)
// 			{
// 				while (line[i] && !ft_iswhitespace(line[i]) && last_tid == whichtoken(line + i, &i))
// 					i++;
// 			}
// 		}
// 	}
// 	return (strs);
// }

void	begin_lexing(char *line)
{
	// char	**strs;
	// int		i;

	// i = 0;
	printf("====[%d]====\n",token_count(line));
	// strs = spliting_based_token(line);
	// while (strs[i])
	// {
	// 	printf("line %d:%s\n",i, strs[i]);
	// 	i++;
	// }
	// printf("line %d:%s\n",i, strs[i]);
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