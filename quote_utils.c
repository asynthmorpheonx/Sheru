/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:03:20 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 22:47:23 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	remove_quote_helper(t_quoter *box, int *len, int *ind, int *qu)
{
	ft_memmove(box->s + box->sap, box->s + box->sap + 1, *len - box->sap);
	if (box->m)
		ft_memmove(box->m + box->sap, box->m + box->sap + 1, *len - box->sap - 1);
	(*len)--;
	ft_memmove(box->s + box->fap, box->s + box->fap + 1, *len - box->fap);
	if (box->m)
		ft_memmove(box->m + box->fap, box->m + box->fap + 1, *len - box->fap - 1);
	(*len)--;
	(*ind) -= 2;
	(*qu) = -1;
}

void	remove_quote(char *str, bool *mask, int len)
{
	t_quoter	box;
	int			i;
	int			qu;

	i = 0;
	qu = -1;
	box.m = mask;
	box.s = str;
	while (str[i])
	{
		if ((str[i] == '"' || str[i] == '\'')
			&& (!mask || (mask && !mask[i])))
		{
			box.sap = i;
			if (qu == -1)
			{
				qu = str[i];
				box.fap = i;
			}
			else if (qu == str[i])
				remove_quote_helper(&box, &len, &i, &qu);
		}
		i++;
	}
}

void	handle_quote(void)
{
	int		i;
	char	*str;
	size_t	olen;

	str = NULL;
	i = 0;
	while (util()->s[i])
	{
		if (util()->a[i] == WORD)
		{
			str = util()->s[i];
			olen = ft_strlen(str);
			remove_quote(str, util()->mask[i], olen);
			if (i && util()->a[i - 1] == HERDOC && olen == ft_strlen(str))
				util()->herdoc_exp = true;
		}
		i++;
	}
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
