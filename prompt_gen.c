/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:19:56 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/24 20:35:03 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static char	*prompt_expansion(char *key)
{
	char	*str;
	char	*dup;

	str = getenv(key);
	if (str)
		dup = safe_substr(str, 0, ft_strlen(str));
	return (str);
}

static size_t	session_name_len(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

static char	*export_session(void)
{
	char		*str;
	char		*ptr;

	str = NULL;
	ptr = prompt_expansion(SESSIO);
	if (ptr)
		str = safe_substr(ptr, 6, session_name_len(ptr + 6));
	return (str);
}

char	*creat_prompt(void)
{
	static char	*str;
	char		*user;
	char		*session;

	if (!str)
	{
		user = prompt_expansion(USR);
		session = export_session();
		str = NULL;
		if (session && user)
		{
			if (*user)
				str = ft_strjoin(user, "@");
			if (*session)
				str = ft_gnl_strjoin(str, session);
			str = ft_gnl_strjoin(str, ":~$ ");
			g_lst_addback(g_new_garbage(str));
		}
	}
	if (!str)
		str = safe_substr("minishell >", 0, 12);
	return (str);
}
