/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:23:17 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/21 02:22:56 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i])
			free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
}

static int	count_word(char const *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			i++;
		if (s[i])
		{
			words++;
			while (s[i]&& s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
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
	while (s[i])
	{
		while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
			i++;
		if (s[i])
		{
			start = i;
			while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
				i++;
			strs[j] = ft_substr(s, start, i - start);
			j++;
		}
	}
	strs[j] = NULL;
	return (strs);
}

char	**white_split(char const *s)
{
	char	**strs;
	int		words;

	if (s == NULL)
		return (NULL);
	words = count_word(s);
	strs = (char **)malloc((words + 1) * (sizeof(char *)));
	if (strs == NULL)
		return (NULL);
	return (filler(strs, s));
}