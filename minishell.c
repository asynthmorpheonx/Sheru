/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:18:13 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/16 16:08:00 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	extract_tokens_count(char **splited_line)
{
	int	i;

	i = 0;
	while (splited_line[i])
		i++;



		
	return (i);
}

int	set_token(char *element)
{
	if (element[0] == '|')
		return (PIPE);
	else if (!ft_strncmp(element, "<<", 3))
		return (HERDOC);
	else if (!ft_strncmp(element, ">>", 3))
		return (APPEND);
	else if (element[0] == '>')
		return (OUDIRECT);
	else if (element[0] == '<')
		return (INDIRECT);
	else
		return (WORD);
}

void	print_tokens(char **element, int *its_token)
{
	int	i;
	char *token_name[6] = {"PIPE", "INDIRECT", "OUTDIRECT", "APPEND", "HEREDOC", "WORD"};

	i = 0;
	while (element[i])
	{
		printf("VALUE \"%s\" it's token \"%s\"\n", element[i], token_name[its_token[i]]);
		i++;
	}
}

void	tokenize_input(char **input, int *token_array)
{
	int	i;

	i = 0;
	while (input[i])
	{
		token_array[i] = set_token(input[i]);
		i++;
	}
}

// void	join_splited(int *arr_token, int range)
// {
// 	int	i;
// 	int	toggle;
// 	int	count;
// 	int	token_id;

// 	i = 0;
// 	count = 0;
// 	token_id = arr_token[0];
// 	toggle = 0;
// 	while (i + 1 < range)
// 	{
// 		if (token_id != arr_token[i + 1])
// 			count++;
// 		i++;
// 	}
// 	if (!count)
// 		count++;
// }

int check_token_syntax(int *token, int range)
{
	int	i;

	i = 0;
	while (i < range)
	{
		if (i == 0
			&& (token[i] == PIPE || token[i] == OUDIRECT
			|| token[i] == APPEND))
			return (0);
		else
		{
			if (token[i] == PIPE && token[i - 1] != WORD && token[i + 1] != WORD)
				return (0);
			else if (token[i] == HERDOC && token[i + 1] != WORD)
				return (0);
			else if (token[i] == APPEND && (token[i - 1] != WORD || token[i + 1] != WORD))
				return (0);
			else if (token[i] == INDIRECT && token[i + 1] != WORD)
				return (0);
			else if (token[i] == OUDIRECT && token[i + 1] != WORD)
				return (0);
		}
		i++;
	}
	return (1);
}

int	extract_y(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	lexer_input(char *str)
{
	char	**parsed_str;
	int		*token_array;

	parsed_str = white_split(str);
	token_array = safe_alloc(extract_tokens_count(parsed_str) * 4, 1);
	tokenize_input(parsed_str, token_array);
	if (!check_token_syntax(token_array, extract_y(parsed_str)))
		printf("token syntax error\n");
	else
		printf("you good\n");
	print_tokens(parsed_str, token_array);
	clear_container();
	printf("hhhhh\n");
}
int main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell>");
		if (!line)
			return (clear_container(), 0);
		lexer_input(line);
	}
}