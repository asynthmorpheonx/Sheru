/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:23:17 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/17 14:41:02 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

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
			while (s[i] && s[i] != ' ' && !(s[i] >= 9 && s[i] <= 13))
				i++;
		}
	}
	return (words);
}

static char	*safe_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (len == 0)
		return (ft_strdup(""));
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)safe_alloc((len + 1) * sizeof(char), 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s + start, len);
	str[len] = '\0';
	return (str);
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
			strs[j] = safe_substr(s, start, i - start);
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
	strs = (char **)safe_alloc((words + 1) * (sizeof(char *)), 0);
	if (strs == NULL)
		return (NULL);
	return (filler(strs, s));
}
