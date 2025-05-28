/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:20 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/28 19:22:43 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	remove_quote(char *str, bool *mask, int len)
{
	int	i;
	int	qu;
	int	fapp;

	i = 0;
	qu = -1;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'') && (!mask || (mask && !mask[i])))
		{
			if (qu == -1)
			{
				qu = str[i];
				fapp = i;
			}
			else
			{
				ft_memmove(str + i, str + i + 1, len - i);
				ft_memmove(mask + i, mask + i + 1, len - i);
				ft_memmove(str + fapp, str + fapp + 1, len - fapp);
				ft_memmove(mask + fapp, mask + fapp + 1, len - fapp);
				qu = -1;
				i -= 2;
			}
		}
		i++;
	}
}

void	handle_quote(void)
{
	int	i;
	char *str;

	str = NULL;
	i = 0;
	while (util()->s[i])
	{
		if (util()->a[i] == WORD)
		{
			str = util()->s[i];
			remove_quote(str, util()->mask[i], ft_strlen(str));
		}
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
