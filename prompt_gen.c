/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 18:19:56 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/29 18:23:12 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

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
	static char	*str;
	char	*ptr;

	if (!str)
	{
		ptr = key_value(SESSIO);
		str = safe_substr(ptr, 6, session_name_len(ptr + 6));
	}
	return (str);
}

// creat an customize shell prompt just to show the user [USER@SESSION]-[OS@SHELL_NAME]
char	*creat_prompt(void)
{
	char	*str;
	char	*user;
	char	*session;

	user = key_value(USR);
	session = export_session();
	str = NULL;
	if (!str && *session && *user)
	{
		if (*user)
			str = ft_strjoin(user, "@");
		if (*session)
			str = ft_gnl_strjoin(str, session);
		str = ft_gnl_strjoin(str, ":~$ ");
	}
	g_lst_addback(g_new_garbage(str));
	return (str);
}