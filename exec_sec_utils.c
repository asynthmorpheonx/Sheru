/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 10:18:15 by hoel-mos          #+#    #+#             */
/*   Updated: 2025/06/23 22:30:11 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int envcount(t_env *env)
{
    int count;
	t_env *current;

	current = env;
    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    return (count);
}

void catcpy(char *tmp, t_env *current)
{
    ft_strcpy(tmp, current->key);
    ft_strcat(tmp, "=");
	if (current->value)
    	ft_strcat(tmp, current->value);
    else
		ft_strcat(tmp, "");
}

char    **env_to_array(t_env *ptr)
{
	int	i;
	char	**anvp;

	i = 0;
	anvp = safe_alloc(sizeof(char *)
		* (envcount(ptr) + 1), 0);
	if (!anvp)
		ult_exit();
	while(ptr)
	{
		anvp[i] = safe_alloc(ft_strlen(ptr->key)
			+ ft_strlen(ptr->value) + 2, 0);
		if (!anvp[i])
			ult_exit();
		catcpy(anvp[i], ptr);
		i++;
		ptr = ptr->next;
	}
	return (anvp);
}
