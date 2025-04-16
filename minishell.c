/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/16 16:53:57 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//it return the token id of the the char that we are dealing with
//it increament the value of 'i' in some cases
int	whichtoken(char *input, int *i)
{
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

// int	syntax_check(int **tokens)
// {
	
// }

char	**spliting_based_token(char *line)
{
	int		i;
	int		j;
	int		k;
	int		last_t_id;
	char	**splited_args;

	i = 0;
	k = 0;
	splited_args = safe_alloc(sizeof(char *) * extact_token_count(line), 1);
	if (!splited_args)
		return (NULL);
	while (ft_iswhitespace(line[i]))
		i++;
	last_t_id = whichtoken(line, &i);
	while (line[i])
	{
		while (ft_iswhitespace(line[i]))
			i++;
		if (line[i])
		{
			j = i;
			while (!ft_iswhitespace(line[i]) && whichtoken(line + i, &i) == last_t_id)
				i++;
			splited_args[k] = ft_substr(line, j, i - j);
			k++;
		}
		i++;
	}
	splited_args[k] = NULL;
	return (splited_args);
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
		printf("======%s======\n",strs[i]);
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