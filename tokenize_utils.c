/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:07:38 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/11 00:08:31 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

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
		return (APP);	
	}	
	else if (input[*i] == '|')
		return (PIPE);
	else if (input[*i] == '<')
		return (IND);
	else if (input[*i] == '>')
		return (OUD);
	else
		return (WORD);
}
int	token_value(char *input)
{
	if (!ft_strncmp(input, "<<", 3))
		return(HERDOC);
	else if (!ft_strncmp(input, ">>", 3))
		return (APP);	
	else if (!ft_strncmp(input, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(input, "<", 2))
		return (IND);
	else if (!ft_strncmp(input, ">", 2))
		return (OUD);
	else
		return (WORD);
}

//count token in the string
bool token_count(char *str)
{
	int	i;
	int	tcount;

	i = 0;
	tcount = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (!str[i])
			break ;
		if ((str[i] == '>' || str[i] == '<')
			&& (str[i + 1] == str[i]))
			i += 2;
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i++;
		else if (!skip_quots(str, &i))
			return (ft_putendl_fd("non end quots", 2), false);
		tcount++;
	}
	util()->t = tcount;
	return (true);
}

// it fills the buffer that is given with and one of the token based on the token_id
void	fill_with_token(char **buffer, int token_id)
{
	if (token_id == PIPE)
		*buffer = ft_strdup("|");
	else if (token_id == IND)
		*buffer = ft_strdup("<");
	else if (token_id == OUD)
		*buffer = ft_strdup(">");
	else if (token_id == APP)
		*buffer = ft_strdup(">>");
	else if (token_id == HERDOC)
		*buffer = ft_strdup("<<");
	g_lst_addback(g_new_garbage(*buffer));
}

// this function breaks string line (input) into small strings that is tokenized 
char	*buffer_filler(char *s, int *i)
{
	int		j;
	int		q;
	char	*str;

	while (ft_iswhitespace(s[*i]))
		(*i)++;
	q = -1;
	j = *i;
	while (s[*i])
	{
		if (q == -1 && (ft_iswhitespace(s[*i]) || ft_ispecial(s[*i])))
			break ;
		else if (s[*i] == '\'' || s[*i] == '"')
		{
			if (q == -1)
				q = *i;
			else if (q >= 0 && s[*i] == s[q])
				q = -1;			
		}
		(*i)++;
	}
	str = safe_substr(s, j, *i - j);
	return (str);
}

// split 
char	**spliting_based_token(char *line)
{
	int		i;
	int		k;
	char	**strs;

	i = 0;
	k = 0;
	strs = safe_alloc((util()->t + 1) * sizeof(char *), 0);
	if (!strs)
		exit (EXIT_FAILURE);
	while (line[i])
	{
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
			strs[k] = buffer_filler(line, &i);
		k++;
	}
	return (strs);
}

// it creates an array of integers that contain token ids of the splited input 
bool	tokenize(void)
{
	int	i;
	int	pi;

	i = 0;
	pi = 0;
	util()->a = safe_alloc(util()->t * sizeof(int), 1);
	if (!util()->a)
		return (false);
	while (i < util()->t)
	{
		util()->a[i] = token_value(util()->s[i]);
		if (util()->a[i] == PIPE)
			pi++;
		i++;
	}
	*ambiguous_ptr() = safe_alloc((pi + 1) * sizeof(bool), 0);
	if (!*ambiguous_ptr())
		return (false);
	return (true);
}
