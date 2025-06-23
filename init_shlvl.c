/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:22:03 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:31:35 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

static int	check_lvl(char	*shlvl)
{
	int	i;

	i = 0;
	while (shlvl[i])
	{
		if (!ft_isdigit(shlvl[i]))
			return (0);
		i++;
	}
	return (ft_atoi(shlvl));
}

void	init_shlvl(void)
{
	int		curr_lvl;
	t_env	*ptr;

	curr_lvl = 1 + check_lvl(key_value("SHLVL"));
	ptr = *envp();
	while (ptr)
	{
		if (!ft_strncmp(ptr->key, "SHLVL", 6))
		{
			delete_one(ptr->value);
			ptr->value = ft_itoa(curr_lvl);
			if (!ptr)
				ult_exit();
			return (g_lst_addback(g_new_garbage(ptr->value)));
		}
		ptr = ptr->next;
	}
	ptr = last_env(*envp());
	ptr->next = safe_alloc(sizeof(t_env), 0);
	ptr->next->key = safe_substr("SHLVL", 0, 5);
	ptr->next->value = ft_itoa(curr_lvl);
	g_lst_addback(g_new_garbage(ptr->next->value));
}
