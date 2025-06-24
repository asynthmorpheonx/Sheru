/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_parse_utlis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:27:22 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/24 21:24:26 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	lenght_both(char **s1, char **s2)
{
	int	i;
	int	len;

	i = 0;
	while (s1 && s1[i])
		i++;
	len = i;
	i = 0;
	while (s2 && s2[i])
		i++;
	len += i;
	return (len);
}

int	key_len(char *str, int pos)
{
	int	i;

	i = pos;
	if (str[pos] == '?' || str[pos] == '$')
		return (pos + 1);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*key_value(char *key)
{
	t_env	*pp;
	char	*tmp;
	int		i;

	if (key[0] == '$' || !key[0])
		return ("");
	else if (key[0] == '?')
		return (exit_code());
	i = key_len(key, 0);
	pp = *envp();
	tmp = ft_substr(key, 0, i);
	if (!tmp)
		ult_exit();
	while (pp)
	{
		if (!ft_memcmp(pp->key, tmp, i + 1))
			return (free(tmp), pp->value);
		pp = pp->next;
	}
	return (free(tmp), "");
}
