/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:21:11 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:02:50 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	expansion_util(int *ind, t_exp *ubox, int end, int tmp)
{
	if (util()->s[*ind][end]
		&& !ft_isalpha(util()->s[*ind][end]))
	{
		ubox->du[ubox->i - 1] = safe_join(ubox->du[ubox->i - 1], util()->s[*ind] + end);
		ubox->mask[ubox->i - 1] = handle_masking(ubox->du[ubox->i - 1], 0, tmp);
	}
	*ind = ubox->i - 1;
	add_suffix(ubox);
	util()->s = ubox->du;
	util()->a = ubox->tokn;
	util()->mask = ubox->mask;
}

bool	begin_expand(int *i, int *j, int *to)
{
	fetch_setter(SET, *i, false);
	if (*to)
		fetch_setter(SET, *i, true);
	expand_value(i, j);
	if (!fetcher()->error)
		return (false);
	util()->a[*i] = -1;
	return (true);
}

void expansion_data(int i, int j, int to, int sto)
{
	while (util()->s[i])
	{
		j = 0;
		to = 1;
		sto = 1;
		while (util()->s[i] && util()->s[i][j] && util()->a[i] > 4)
		{
			fetch_setter(RESET, 0, 0);
			if (util()->s[i][j] == '\'' && to)
				switch_toggles(&sto);
			else if (util()->s[i][j] == '"' && sto)
				switch_toggles(&to);
			else if ((!i || (i && util()->a[i - 1] != 4))
				&& util()->s[i][j] == '$' && sto)
			{
				if (!begin_expand(&i, &j, &to))
					continue;
			}
			j++;
		}
		i++;
	}
}
