/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/17 14:38:25 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

//it return the token id of the the char that we are dealing with
//it increament the value of 'i' in some cases
int	whichtoken(char *input, int *i)
{
	(void)i;
	if (!ft_strncmp(input, "<<", 2))
	{
		(*i)++;
		return(HERDOC);
	}
	else if (!ft_strncmp(input, ">>", 2))
	{
		(*i)++;
		return (APPEND);
	}	
	else if (input[0] == '|')
		return (PIPE);
	else if (input[0] == '<')
		return (INDIRECT);
	else if (input[0] == '>')
		return (OUDIRECT);
	else
		return (-1);
}

int	give_id_value(char *input)
{
	if (!ft_strncmp(input, "<<", 2))
		return(HERDOC);
	else if (!ft_strncmp(input, ">>", 2))
		return (APPEND);	
	else if (input[0] == '|')
		return (PIPE);
	else if (input[0] == '<')
		return (INDIRECT);
	else if (input[0] == '>')
		return (OUDIRECT);
	else
		return (-1);
}

//checks the bytes if it's an white space
int	ft_iswhitespace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

//it count how much different tokens does the user put
int	extact_token_count(char *input)
{
	int	i;
	int	tcount;
	int	lastoken;
	int	toggle;

	i = 0;
	toggle = 1;
	tcount = 0;
	lastoken = whichtoken(input, &i);
	while (input[i])
	{
		if ((!ft_iswhitespace(input[i]) && toggle == 1) || whichtoken(input + i, &i) != lastoken)
		{
			tcount++;
			toggle = 0;
		}
		else if (ft_iswhitespace(input[i]))
			toggle = 1;
		lastoken = whichtoken(input + i - 1, &i);
			i++;
	}
	return (tcount);
}

// int	fill_with_token(char *buffer, int token_id)
// {
// 	char	*tokens;

// 	if (token_id == PIPE)
// 		buffer = safe
// }

char	**spliting_based_token(char *line)
{
	int		i;
	int		j;
	int		k;
	int		last_tid;
	char	**strs;

	i = 0;
	k = 0;
	strs = safe_alloc((extact_token_count(line) + 1) * sizeof(char *), 0);
	if (!strs)
		return (NULL);
	last_tid = whichtoken(line, &i);
	while(line[i])
	{
		while (ft_iswhitespace(line[i]))
			i++;
		if(line[i])
		{
			j = i;
			while(line[i] && !ft_iswhitespace(line[i]) && give_id_value(line + i) == last_tid)
				i++;
			strs[k] = ft_substr(line, j, i - j);
			if (!strs[k])
				return (NULL);
			k++;
			last_tid = whichtoken(line + i, &i);
		}
	}
	return (strs);
}

void	begin_lexing(char *line)
{
	char	**strs;
	int		i;

	i = 0;
	printf("====[%d]====\n",extact_token_count(line));
	strs = spliting_based_token(line);
	while (strs[i])
	{
		printf("line %d:%s\n",i, strs[i]);
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