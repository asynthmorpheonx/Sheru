// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export_advanced.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/17 22:28:12 by mel-mouh          #+#    #+#             */
// /*   Updated: 2025/06/17 23:50:42 by mel-mouh         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <mini_shell.h>

// bool	check_exp_pre(char *arg, int *i)
// {
// 	if (arg && ft_isdigit(*arg))
// 		return (false);
// 	while (arg[*i] && arg[*i] != '=' && arg[*i] != '+')
// 	{
// 		if (!ft_isalpha(arg[*i]) && arg[*i] != '_')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }

// bool	check_operator(char *arg, int *ind, int *mode)
// {
// 	if (arg[*ind] == '=')
// 	{
// 		*ind += 1;
// 		*mode = ESET;
// 	}
// 	else if (arg[*ind] == '+' && arg[*ind + 1] == '=')
// 	{
// 		*ind += 2;
// 		*mode = EAPP;
// 	}
// 	else if (!arg[*ind])
// 		*mode = ENOT;
// 	else
// 		return (false);
// 	return (true);
// }

// bool	export_syntax(char *arg, int *mode, int *ind)
// {
// 	int	i;

// 	i = 0;
// 	if (!check_exp_pre(arg, &i))
// 		return (false);
// 	if (!check_operator(arg, &i, mode))
// 		return (false);
// 	*ind = i;
// 	return (true);
// }

// void	export_data(char *key, int len, char *data, int mode)
// {
// 	t_env	*ptr;
// 	t_env	*tmp;

// 	ptr = *envp();
// 	while (ptr)
// 	{
// 		if (!ft_strncmp(key, ptr->key, len) && !ptr->key[len])
// 		{
// 			if (mode == ESET)
// 				ptr->value = data;
// 			else if (mode == EAPP)
// 				safe_join(ptr->value, data);
// 			return ;
// 		}
// 		ptr = ptr->next;
// 	}
// 	tmp = safe_alloc(sizeof(t_env), 0);
// 	tmp->key = safe_substr(key, 0, len);
// 	tmp->value = data;
// }

// void	build_data(char **args)
// {
// 	int	i;
// 	int	start;
// 	int	mode;

// 	i = 0;
// 	while (args[i])
// 	{
// 		if (export_syntax(args[i], &mode, &start))
// 			export_data(args[i], i, args[i], mode);
// 		else
// 		{
// 			ft_putstr_fd("export :'", 2);
// 			ft_putstr_fd(args[i], 2);
// 			ft_putstr_fd("': not a valid identifier", 2);
// 		}
// 		i++;
// 	}
// }

// void	ft_export(t_data *cmd)
// {
// 	if (!cmd->cmd[1])
// 		export_print(envp());
// 	else
// 		build_data(cmd->cmd + 1);
// }