/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:07:38 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

bool	token_count(char *str)
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
			return (ft_putendl_fd("sheu: syntax error non end quots", 2),
				code_setter(2), false);
		tcount++;
	}
	util()->t = tcount;
	return (true);
}

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

char	**spliting_based_token(char *line)
{
	int		i;
	int		k;
	char	**strs;

	i = 0;
	k = 0;
	strs = safe_alloc((util()->t + 1) * sizeof(char *), 0);
	if (!strs)
		ult_exit();
	while (line[i])
	{
		while (ft_iswhitespace(line[i]))
			i++;
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			fill_with_token(strs + k, whichtoken(line, &i));
			i++;
		}
		else if (line[i])
			strs[k] = buffer_filler(line, &i);
		k++;
	}
	return (strs);
}
