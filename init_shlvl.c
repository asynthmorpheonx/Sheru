/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:22:03 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

static int	check_lvl(char	*shlvl)
{
	int	i;
	int	nbr;

	i = 0;
	while (shlvl[i])
	{
		if (!ft_isdigit(shlvl[i]))
			return (0);
		i++;
	}
	nbr = ft_atoi(shlvl);
	if (nbr >= 999)
		return (ft_putstr_fd("sheru: warning: shell level (", 2),
			ft_putnbr_fd(nbr + 1, 2),
			ft_putendl_fd(") too high, resetting to 1", 2), 0);
	return (nbr);
}

void	init_shlvl(void)
{
	int		curr_lvl;
	t_env	*ptr;

	ptr = *envp();
	curr_lvl = 1;
	if (ptr)
		curr_lvl = 1 + check_lvl(key_value("SHLVL"));
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
	ptr = safe_alloc(sizeof(t_env), 0);
	ptr->key = safe_substr("SHLVL", 0, 5);
	ptr->value = ft_itoa(curr_lvl);
	add_to_envp(envp(), ptr);
	g_lst_addback(g_new_garbage(ptr->value));
}
