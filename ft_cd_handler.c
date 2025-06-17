/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:14:56 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/17 22:16:45 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static void	update_oldwd(char *new_oldwd, t_env *oldwd)
{
	if (!oldwd)
	{
		oldwd = safe_alloc(sizeof(t_env), 0);
		if (!oldwd)
			ult_exit();
		oldwd->key = "OLDPWD";
		add_last_env(oldwd);
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
		nwd->key = "PWD";
		add_last_env(nwd);
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
			return (ft_putendl_fd("cd: HOME not set", 2));
		path = safe_substr(path, 0, ft_strlen(path));
	}
	else
		path = safe_substr(cmd->cmd[1], 0, ft_strlen(cmd->cmd[1]));
	if (chdir(path))
		return (perror(cmd->cmd[1]));
	update_pwd(getcwd(offs()->pwd, 4096), NULL);
}
