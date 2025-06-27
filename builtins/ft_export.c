/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 21:40:29 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

int	ft_varcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && (s1[i] != '=' && s2[i] != '='))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (s1[i - 1] - s2[i - 1]);
}

void	export_print(t_env **env)
{
	char	**tenv;
	t_env	*tmp;

	int (i), (check);
	tenv = env_to_array(*env);
	sort_tenv(tenv);
	i = 0;
	while (tenv[i])
	{
		tmp = *env;
		while (tmp)
		{
			check = ft_varcmp(tmp->key, tenv[i]);
			if (check == 0)
			{
				if (tmp->value)
					printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
				else
					printf("declare -x %s\n", tmp->key);
			}
			tmp = tmp->next;
		}
		i++;
	}
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

void	ft_export(t_data *cmd)
{
	if (!cmd->cmd[1])
		export_print(envp());
	else
		build_data(cmd->cmd + 1);
}
