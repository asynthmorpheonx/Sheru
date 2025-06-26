/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 00:04:58 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

char	*ft_readline(void)
{
	write(1, "> ", 2);
	return (readline(""));
}

void	begin_lexing(char *line)
{
	reset_data_box();
	if (!token_count(line))
		return ;
	util()->s = spliting_based_token(line);
	if (tokenize() && syntax_check())
	{
		if (util()->herdoc > 16)
		{
			ft_putendl_fd("maximum here-document count exceeded", 2);
			clear_container();
			exit(2);
		}
		creat_mask();
		expansion_data(0, 0, 1, 1);
		handle_quote();
		if (!stor_in_list(util()->s, util()->a, box()))
			return ;
		if (util()->herdoc)
			herdoc_job();
		if (*process_status() != INTERRUPTED)
			execute_command(*box());
		reset_util_box();
	}
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	signal(SIGINT, interupt_handle);
	signal(SIGQUIT, SIG_IGN);
	make_env(env, envp(), 0, 0);
	code_setter(0);
	init_shlvl();
	while (1)
	{
		*process_status() = SCANIN;
		line = readline(creat_prompt());
		if (!line)
		{
			write(1, "exit\n", 5);
			return (clear_container(), 0);
		}
		if (*line)
		{
			add_history(line);
			begin_lexing(line);
		}
	}
}
