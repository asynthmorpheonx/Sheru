/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_hand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:29:08 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:40:51 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

void	interupt_handle(int sig_num)
{
	if (*process_status() != WAITIN)
	{
		if (*process_status() == HERDOC_READ)
		{
			*process_status() = INTERRUPTED;
			rl_done = 1;
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	code_setter(128 + sig_num);
}
