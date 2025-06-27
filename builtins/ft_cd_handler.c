/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:14:56 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

static void	update_oldwd(char *new_oldwd, t_env *oldwd)
{
	if (!oldwd)
	{
		oldwd = safe_alloc(sizeof(t_env), 0);
		if (!oldwd)
			ult_exit();
		oldwd->key = safe_substr("OLDPWD", 0, 6);
		last_env(*envp())->next = oldwd;
	}
	oldwd->value = new_oldwd;
}

static void	update_pwd(char *new_wd, t_env *tmp)
{
	t_env	*owd;
	t_env	*nwd;

	tmp = *envp();
	owd = NULL;
	nwd = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PWD", 4))
			nwd = tmp;
		else if (!ft_strncmp(tmp->key, "OLDPWD", 7))
			owd = tmp;
		tmp = tmp->next;
	}
	if (!nwd)
	{
		nwd = safe_alloc(sizeof(t_env), 0);
		nwd->key = safe_substr("PWD", 0, 3);
		last_env(*envp())->next = nwd;
	}
	else if (nwd)
		update_oldwd(nwd->value, owd);
	nwd->value = safe_substr(new_wd, 0, ft_strlen(new_wd));
	if (!nwd->value)
		ult_exit();
}

void	ft_cd(t_data *cmd)
{
	char	*path;

	if (!cmd->cmd[1] || (cmd->cmd[1] && !*cmd->cmd[1]))
	{
		path = key_value("HOME");
		if (!*path)
			return (code_setter(1),
				ft_putendl_fd("sheru: cd: HOME not set", 2));
	}
	else if (cmd->cmd[2])
		return (code_setter(1),
			ft_putendl_fd("sheru: cd: too many arguments", 2));
	else
		path = cmd->cmd[1];
	if (chdir(path))
		return (code_setter(1), perror(cmd->cmd[1]));
	path = getcwd(NULL, 0);
	if (!path)
		redir_msg_err(3, NULL);
	else
	{
		free(path);
		code_setter(0);
		update_pwd(getcwd(offs()->pwd, 4096), NULL);
	}
}
