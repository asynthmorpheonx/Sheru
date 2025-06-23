/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:54:42 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:14:24 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	switch_toggles(int *toggle)
{
	if (*toggle)
		*toggle = 0;
	else
		*toggle = 1;
}

void	fetch_setter(bool mode, int i, bool is_full)
{
	if (mode)
	{
		if (i && util()->a[i - 1] < PIPE)
			fetcher()->flage = true;
		fetcher()->full_exp = is_full;
	}
	else
	{
		fetcher()->flage = false;
		fetcher()->error = false;
		fetcher()->full_exp = false;
	}
}

int	join_preffix(int end, t_exp *ptr)
{
	int	i;

	i = 0;
	while (i < end)
	{
		ptr->du[i] = util()->s[i];
		ptr->tokn[i] = util()->a[i];
		ptr->mask[i] = util()->mask[i];
		i++;
	}
	return (i);
}

void	add_extended(t_exp *ubox)
{
	while (ubox->extend[ubox->j])
	{
		ubox->du[ubox->i] = ubox->extend[ubox->j];
		ubox->tokn[ubox->i] = WORD;
		ubox->mask[ubox->i] = safe_alloc(ft_strlen(ubox->extend[ubox->j]), 0);
		ft_memset(ubox->mask[ubox->i], true, ft_strlen(ubox->extend[ubox->j]));
		ubox->i++;
		ubox->j++;
	}
}

void	add_suffix(t_exp *ubox)
{
	while (ubox->i < ubox->len)
	{
		ubox->du[ubox->i] = util()->s[ubox->i - ubox->j + 1];
		ubox->tokn[ubox->i] = util()->a[ubox->i - ubox->j + 1];
		ubox->mask[ubox->i] = util()->mask[ubox->i - ubox->j + 1];
		ubox->i++;
	}
}
