/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 00:28:53 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/16 21:34:18 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static char	**ft_free(char **strs, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	count_word(char const *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (is_ifs(s[i]))
			i++;
		if (s[i])
		{
			words++;
			while (s[i] && !is_ifs(s[i]))
				i++;
		}
	}
	return (words);
}

static char	**filler(char **strs, char const *s)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	while (s[j])
	{
		while (is_ifs(s[j]))
			j++;
		if (s[j])
		{
			start = j;
			while (s[j] && !is_ifs(s[j]))
				j++;
			strs[i] = ft_substr((char *)s, start, j - start);
			printf(" 3 buts li leaked %s\n", strs[i]);
			if (!strs[i])
				return (ft_free(strs, i));
			i++;
		}
	}
	return (strs);
}

// it's split the char *s by ifs character
char	**ifs_split(char const *s)
{
	char	**strs;
	int		words;

	if (!s)
		return (NULL);
	words = count_word(s);
	strs = safe_alloc((words + 1) * (sizeof(char *)), 0);
	if (!strs)
		return (NULL);
	return (filler(strs, s));
}