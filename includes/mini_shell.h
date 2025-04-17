/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:53:04 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/17 14:38:14 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include <libft.h>
# include <ft_printf.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <heap_controller.h>

typedef enum e_token
{
	PIPE,
	INDIRECT,
	OUDIRECT,
	APPEND,
	HERDOC,
	WORD
}	t_token;

void	*safe_alloc(size_t byts_count, int mode);
t_list	**g_container(void);
char	**white_split(char const *s);
void	ft_free(char **strs);

#endif