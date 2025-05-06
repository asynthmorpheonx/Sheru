/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:20 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/06 22:06:15 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

// it returns count of byts but the closed quotes execluded.
size_t	size_quot(char *str)
{
	size_t	i;
	size_t	k;
	int		j;

	i = 0;
	j = -1;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (j == -1)
				j = i;
			else if (j >= 0 && str[j] == str[i])
			{
				j = -1;
				k += 2;
			}
		}
		i++;
	}
	return (i - k);
}

// this function the something that i cant explain.
void	remove_quote(size_t len, char **str, int i, int j)
{
	char	*ptr;
	int		q;

	q = -1;
	ptr = safe_alloc((len + 1) * sizeof(char), 0);
	if (!ptr)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			if (q == -1 || (*str)[q] == (*str)[i])
			{
				if (q == -1)
					q = i;
				else
					q = -1;
				i++;
				continue ;
			}
		}
		ptr[j++] = (*str)[i++];
	}
	delete_one(*str);
	*str = ptr;
}

//this function recreate the string data for handling quote
void	handle_quote(void)
{
	int		i;
	size_t	len;

	i = 0;
	while (util()->s[i])
	{
		len = size_quot(util()->s[i]);
		if (util()->a[i] == WORD && ft_strlen(util()->s[i]) != len)
			remove_quote(len, &util()->s[i], 0, 0);
		i++;
	}
}

//it skips till '\0' or whitespace or it counter another token
int	skip_quots(char *line, int *i)
{
	int	j;
	int	toggle;

	toggle = 1;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (toggle)
			{
				j = (*i);
				toggle = 0;
			}
			else if (line[*i] == line[j])
				toggle = 1;
		}
		else if ((ft_iswhitespace(line[*i]) || ft_ispecial(line[*i])) && toggle)
			break ;
		(*i)++;
	}
	if (toggle)
		return (1);
	return (0);
}
