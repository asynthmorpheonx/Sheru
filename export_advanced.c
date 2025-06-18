/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:28:12 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/18 16:28:59 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

bool	check_exp_pre(char *arg, int *i)
{
	if (arg && !ft_isalpha(*arg) && *arg != '_')
		return (false);
	while (arg[*i] && arg[*i] != '=' && arg[*i] != '+')
	{
		if (!ft_isalnum(arg[*i]) && arg[*i] != '_')
			return (false);
		(*i)++;
	}
	return (true);
}

bool	check_operator(char *arg, int *ind, int *mode)
{
	if (arg[*ind] == '=')
	{
		*ind += 1;
		*mode = ESET;
	}
	else if (arg[*ind] == '+' && arg[*ind + 1] == '=')
	{
		*ind += 2;
		*mode = EAPP;
	}
	else if (!arg[*ind])
		*mode = ENOT;
	else
		return (false);
	return (true);
}

bool	export_syntax(char *arg, int *mode, int *ind)
{
	int	i;

	i = 0;
	if (!check_exp_pre(arg, &i))
		return (false);
	if (!check_operator(arg, &i, mode))
		return (false);
	*ind = i;
	return (true);
}

char	*ft_keydup(const char *s1)
{
	size_t	i;
	char	*str;

	i = 0;
	str = safe_alloc(ft_strlen(s1) + 1, 0);
	if (!str)
		ult_exit();
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}

void	handle_exp(int mode, t_env *ptr, char *data)
{
	if (mode == ESET)
	{
		if (ptr->value)
			delete_one(ptr->value);
		ptr->value = ft_keydup(data);
	}
	else if (mode == EAPP)
		ptr->value = safe_join(ptr->value, data);
}

void	export_data(char *key, int len, char *data, int mode)
{
	t_env	*ptr;
	t_env	*tmp;

	ptr = *envp();
	while (ptr)
	{
		if (!ft_strncmp(key, ptr->key, len - mode) && !ptr->key[len - mode])
			return (handle_exp(mode, ptr, data));
		ptr = ptr->next;
	}
	tmp = safe_alloc(sizeof(t_env), 0);
	if (mode == ENOT)
		tmp->key = ft_keydup(key);
	else
		tmp->key = safe_substr(key, 0, len - mode);
	if (*data)
		tmp->value = ft_keydup(data);
	last_env(*envp())->next = tmp;
}

void	build_data(char **args)
{
	int	i;
	int	start;
	int	mode;

	i = 0;
	while (args[i])
	{
		if (export_syntax(args[i], &mode, &start))
			export_data(args[i], start, args[i] + start, mode);
		else
		{
			ft_putstr_fd("export :'", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			code_setter(1);
		}
		i++;
	}
}

void	ft_export(t_data *cmd)
{
	if (!cmd->cmd[1])
		export_print(envp());
	else
		build_data(cmd->cmd + 1);
}