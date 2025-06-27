/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aditional_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:23:10 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

int	ft_iswhitespace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	ft_ispecial(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

bool	is_ifs(int c)
{
	char	*ptr;
	int		i;

	ptr = key_value("IFS");
	if (*ptr)
	{
		i = 0;
		while (ptr[i])
		{
			if (ptr[i] == c)
				return (true);
			i++;
		}
		return (false);
	}
	return (c == '\n' || c == '\t' || c == ' ');
}

char	*safe_substr(char *str, unsigned int start, size_t len)
{
	char	*pp;

	if (len)
	{
		pp = ft_substr(str, start, len);
		if (!pp)
			ult_exit();
		g_lst_addback(g_new_garbage(pp));
		return (pp);
	}
	return (NULL);
}

char	*safe_join(char *s1, char *s2)
{
	char	*pp;

	pp = ft_strjoin(s1, s2);
	if (!pp)
		ult_exit();
	delete_one(s1);
	g_lst_addback(g_new_garbage(pp));
	return (pp);
}
