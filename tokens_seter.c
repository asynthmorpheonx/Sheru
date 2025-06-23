/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_seter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 22:34:36 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/23 22:35:33 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

int	whichtoken(char *input, int *i)
{
	if (!ft_strncmp(input + *i, "<<", 2))
	{
		(*i) += 1;
		return(HERDOC);
	}
	else if (!ft_strncmp(input + *i, ">>", 2))
	{
		(*i) += 1;
		return (APP);	
	}	
	else if (input[*i] == '|')
		return (PIPE);
	else if (input[*i] == '<')
		return (IND);
	else if (input[*i] == '>')
		return (OUD);
	else
		return (WORD);
}

int	token_value(char *input)
{
	if (!ft_strncmp(input, "<<", 3))
		return(HERDOC);
	else if (!ft_strncmp(input, ">>", 3))
		return (APP);	
	else if (!ft_strncmp(input, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(input, "<", 2))
		return (IND);
	else if (!ft_strncmp(input, ">", 2))
		return (OUD);
	else
		return (WORD);
}

bool	tokenize(void)
{
	int	i;

	i = 0;
	util()->a = safe_alloc(util()->t * sizeof(int), 1);
	if (!util()->a)
		return (false);
	while (i < util()->t)
	{
		util()->a[i] = token_value(util()->s[i]);
		if (util()->a[i] == HERDOC)
			(util()->herdoc) += 1;
		i++;
	}
	return (true);
}
