/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:29:08 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/25 16:59:35 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

void	interupt_handle(int sig_num)
{
	if (sig_num == SIGINT && *process_status() != INTERRUPTED)
	{
		if (*process_status() == HERDOC_READ)
		{
			*process_status() = INTERRUPTED;
			rl_done = 1;
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		code_setter(130);
	}
}
