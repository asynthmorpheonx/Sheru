/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:21:11 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/29 22:00:23 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static bool	*handle_masking(char *str, int start, int len)
{
	bool	*mask;
	int		i;

	i = start;
	mask = safe_alloc(ft_strlen(str), 0);
	if (!mask)
		ult_exit();
	while (str[i] && i - start < len)
	{
		mask[i] = true;
		i++;
	}
	return (mask);
}

void switch_toggles(int *toggle)
{
	if (*toggle)
		*toggle = 0;
	else
		*toggle = 1;
}

// it's function that set the fetch struct into store previous token and type expansion(full/normal)
void fetch_setter(bool mode, int i, bool is_full)
{
	if (mode)
	{
		if (i && util()->a[i - 1] <= PIPE)
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

// it extend the util().s and update the the array
static void extend_key(int *index, int *start, char *value, int end)
{
	int		i;
	int		j;
	int		u;
	int		len;
	char	*tmp;
	char	**extnd;
	char	**dup;
	bool	**mask;
	int		*a_dup;

	i = 0;
	j = 0;
	u = 0;
	tmp = NULL;
	if (*start)
		tmp = ft_substr(util()->s[*index], 0, *start);
	extnd = ifs_split(value);
	if (!extnd)
		ult_exit() ;
	if (*start && is_ifs(*value))
		len = lenght_both(extnd, util()->s);
	else
		len = lenght_both(extnd, util()->s) - 1;
	dup = safe_alloc((len + 1) * sizeof(char *), 0);
	a_dup = safe_alloc(len * sizeof(int), 0);
	mask = safe_alloc(len * sizeof(bool *), 0);
	if (!dup || !a_dup)
	{
		if (tmp)
			free(tmp);
		ult_exit();
	}
	while (i < *index)
	{
		dup[i] = util()->s[i];
		a_dup[i] = util()->a[i];
		mask[i] = util()->mask[i];
		i++;
	}
	if (tmp && !is_ifs(*value))
	{
		dup[i] = safe_join(tmp, extnd[j]);
		mask[i] = handle_masking(dup[i], *start, ft_strlen(value));
		a_dup[i] = WORD;
		j++;
		i++;
	}
	else if (tmp)
	{
		g_lst_addback(g_new_garbage(tmp));
		mask[i] = safe_alloc(ft_strlen(tmp), 0);
		ft_memset(mask[i], true, ft_strlen(tmp));
		dup[i++] = tmp;
		a_dup[i - 1] = WORD;
	}
	while (extnd[j])
	{
		dup[i] = extnd[j];
		a_dup[i] = WORD;
		mask[i] = safe_alloc(ft_strlen(extnd[j]), 0);
		ft_memset(mask[i], true, ft_strlen(extnd[j]));
		i++;
		j++;
	}
	u = ft_strlen(dup[i - 1]);
	if (util()->s[*index][end] && !ft_isalpha(util()->s[*index][end]))
	{
		dup[i - 1] = safe_join(dup[i - 1], util()->s[*index] + end);
		mask[i - 1] = handle_masking(dup[i - 1], 0, u);
	}
	*index = i - 1;
	*start = u;
	while (i < len)
	{
		dup[i] = util()->s[i - j + 1];
		a_dup[i] = util()->a[i - j + 1];
		mask[i] = util()->mask[i - j + 1];
		i++;
	}
	util()->s = dup;
	util()->a = a_dup;
	util()->mask = mask;
}

static void	replace_key_to_value(int *ind, int *strt, int k_len, char *value)
{
	char	*dup;
	bool	*mask;
	int		var;
	int		len;

	dup = NULL;
	mask = NULL;
	len = ft_strlen(value);
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
		*strt = len;
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

// this function expand the key found in util().s[index] and return the index after the expand
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

// TODO : handle quote removal and empty value of variable
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
			else if ((!i || (i && util()->a[i - 1] != HERDOC)) && util()->s[i][j] == '$' && sto)
			{
				fetch_setter(SET, i, false);
				if (to)
					fetch_setter(SET, i, true);
				expand_value(&i, &j);
				if (!fetcher()->error)
					continue;
				util()->a[i] = -1;
			}
			j++;
		}
		i++;
	}
}
