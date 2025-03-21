/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:18:13 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/03/21 03:58:53 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lexer_input(char *str)
{
	char	**parsed_str;

	parsed_str = white_split(str);
	for (int i = 0; parsed_str[i]; i++)
		printf("========= [%s] =========\n", parsed_str[i]);
	ft_free(parsed_str);
	free(str);
}

int main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell>");
		printf("the entered input ==> %s\n", line);
		if (!line)
			return (clear_container(), 0);
		lexer_input(line);
	}
}