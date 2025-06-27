/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_boxs_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 23:24:17 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/27 14:26:05 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sheru.h>

void	clean_lst(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		delete_one(str[i]);
		i++;
	}
}

void	reset_data_box(void)
{
	t_data	*next;

	if (*box())
	{
		next = *box();
		while (*box())
		{
			clean_lst((*box())->cmd);
			if ((*box())->file.infile)
				delete_one((*box())->file.i_type);
			clean_lst((*box())->file.infile);
			if ((*box())->file.outfile)
				delete_one((*box())->file.o_type);
			clean_lst((*box())->file.outfile);
			next = (*box())->next;
			delete_one(*box());
			*box() = next;
		}
	}
}

void	reset_util_box(void)
{
	if (util()->s)
		delete_one(util()->s);
	if (util()->a)
		delete_one(util()->a);
	if (util()->mask)
		delete_one(util()->mask);
	if (*util()->ports)
		ft_bzero(util()->ports, 16 * sizeof(int));
	util()->herdoc = 0;
	util()->t = 0;
}
