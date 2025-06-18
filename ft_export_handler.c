/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 22:21:28 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/18 16:30:40 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	ft_varcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while(s1[i] && (s1[i] != '=' && s2[i] != '='))
	{
		if(s1[i] != s2[i])
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
	tenv = env_to_array(env);
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
