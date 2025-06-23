/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:21:11 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 22:31:52 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void switch_toggles(int *toggle)
{
	if (*toggle)
		*toggle = 0;
	else
		*toggle = 1;
}

void fetch_setter(bool mode, int i, bool is_full)
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

void	handle_if_begin_with_ifs(int start, t_exp *ubox, char *value)
{
	char	*tmp;
	
	if (start)
	{
		tmp = ft_substr(util()->s[ubox->i], 0, start);
		if (!tmp)
			ult_exit();
		if (!is_ifs(*value))
		{
			ubox->du[ubox->i] = safe_join(tmp, ubox->extend[ubox->j]);
			ubox->mask[ubox->i] = handle_masking(ubox->du[ubox->i],
				start, ft_strlen(value));
			ubox->tokn[ubox->i] = WORD;
			ubox->j++;
		}
		else
		{
			g_lst_addback(g_new_garbage(tmp));
			ubox->mask[ubox->i] = safe_alloc(ft_strlen(tmp), 0);
			ft_memset(ubox->mask[ubox->i], true, ft_strlen(tmp));
			ubox->du[ubox->i] = tmp;
			ubox->tokn[ubox->i] = WORD;
		}
		ubox->i++;
	}
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

static void extend_key(int *index, int *start, char *value, int end)
{
	t_exp	u_box;
	int		tmp;

	u_box.i = 0;
	u_box.j = 0;
	u_box.extend = ifs_split(value);
	if (!u_box.extend)
		ult_exit() ;
	if (*start && is_ifs(*value))
		u_box.len = lenght_both(u_box.extend, util()->s);
	else
		u_box.len = lenght_both(u_box.extend, util()->s) - 1;
	u_box.du = safe_alloc((u_box.len + 1) * sizeof(char *), 0);
	u_box.tokn = safe_alloc(u_box.len * sizeof(int), 0);
	u_box.mask = safe_alloc(u_box.len * sizeof(bool *), 0);
	if (!u_box.du || !u_box.tokn)
		ult_exit();
	u_box.i = join_preffix(*index, &u_box);
	handle_if_begin_with_ifs(*start, &u_box, value);
	add_extended(&u_box);
	tmp = ft_strlen(u_box.du[u_box.i - 1]);
	expansion_util(index, &u_box, end, tmp);
	*start = tmp;
}

static void	replace_key_to_value(int *ind, int *strt, int k_len, char *value)
{
	char	*dup;
	bool	*mask;
	int		var;
	int		len;

	dup = NULL;
	mask = NULL;
	len = ft_strlen(value) + 1;
	if (*strt)
		dup = ft_substr(util()->s[*ind], 0, *strt);
	dup = ft_gnl_strjoin(dup, value);
	var = ft_strlen(dup);
	dup = safe_join(dup, util()->s[*ind] + k_len);
	delete_one(util()->s[*ind]);
	delete_one(util()->mask[*ind]);
	util()->s[*ind] = dup;
	util()->mask[*ind] = handle_masking(dup, *strt, len);
	if (*value)
		*strt = len - 1;
}

static bool	check_value(char *str)
{
	int	i;
	int	toggle;
	int	count;

	i = 0;
	toggle = 1;
	count = 0;
	if (str && !*str)
		return (false);
	while (str[i])
	{
		if (!is_ifs(str[i]) && toggle)
		{
			count++;
			toggle = 0;
			if (count >	1)
				return (false);
		}
		else if (is_ifs(str[i]))
			toggle = 1;
		i++;
	}
	if (!count)
		return (false);
	return (true);
}

static void expand_value(int *index, int *start)
{
	char	*dup;
	char	*value;
	bool	status;
	int		i;

	i = key_len(util()->s[*index], *start + 1);
	dup = NULL;
	value = key_value(util()->s[*index] + *start + 1);
	status = check_value(value);
	if (fetcher()->flage && fetcher()->full_exp && !status)
		fetcher()->error = true;
	else if (*value && fetcher()->full_exp && !status)
		extend_key(index, start, value, i);
	else
		replace_key_to_value(index, start, i, value);
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
