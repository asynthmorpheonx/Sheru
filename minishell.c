/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:18:13 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/19 01:11:30 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int main(int ac, char **av, char **envp)
{
	ft_printf("ac %d\n av %c\n, envp %s\n",ac, av[1], *envp);
	ft_printf("hello world from free fire... i mean minishell\n");
}