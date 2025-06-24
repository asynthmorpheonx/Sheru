/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask_creation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:01:09 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/24 01:10:45 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

bool	*handle_masking(char *str, int start, int len)
{
	bool	*mask;
	int		i;

	i = start;
	mask = safe_alloc(ft_strlen(str) + 1, 0);
	if (!mask)
		ult_exit();
	if (!*str)
	{
		mask[0] = true;
		return (mask);
	}
	while (i < len + start - 1)
	{
		mask[i] = true;
		i++;
	}
	return (mask);
}

bool	*mask_joining(bool *o_mask, char *pre, char *suff)
{
	bool	*new_mask;
	int		index;
	int		i;

	i = 0;
	index = ft_strlen(pre);
	new_mask = safe_alloc(ft_strlen(suff) + index, 0);
	if (!new_mask)
		return (NULL);
	while (i < index)
	{
		new_mask[i] = o_mask[i];
		i++;
	}
	i = 0;
	while (suff[i])
	{
		new_mask[i + index] = true;
		i++;
	}
	delete_one(o_mask);
	return (new_mask);
}

bool	creat_mask(void)
{
	bool	**mask;
	int		i;

	i = 0;
	mask = safe_alloc(util()->t * sizeof(bool *), 0);
	if (!mask)
		ult_exit();
	while (util()->s[i])
	{
		if (util()->a[i] == WORD)
		{
			mask[i] = safe_alloc(ft_strlen(util()->s[i]) + 1, 0);
			if (!mask[i])
				ult_exit();
		}
		i++;
	}
	util()->mask = mask;
	return (true);
}
