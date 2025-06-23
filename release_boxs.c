/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release_boxs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:18:05 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 23:43:29 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_data	**box(void)
{
	static t_data	*pp;

	return (&pp);
}

t_prstat	*process_status(void)
{
	static t_prstat	var;

	return (&var);
}

t_env	**envp(void)
{
	static t_env	*pp;

	return (&pp);
}

t_ferror	*fetcher(void)
{
	static t_ferror	pp;

	return (&pp);
}

t_utils	*util(void)
{
	static t_utils	pp;

	return (&pp);
}
