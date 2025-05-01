/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/04/30 23:47:43 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

//it return the token id of the the char that we are dealing with
//it increament the value of 'i' in some cases

t_data	**box(void)
{
	static t_data	*pp;

	return (&pp);
}

t_utils	*util(void)
{
	static t_utils	pp;

	return (&pp);
}

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
	if (!ft_strncmp(input, "<<", 2))
		return(HERDOC);
	else if (!ft_strncmp(input, ">>", 2))
		return (APP);	
	else if (input[0] == '|')
		return (PIPE);
	else if (input[0] == '<')
		return (IND);
	else if (input[0] == '>')
		return (OUD);
	else
		return (WORD);
}

//checks the bytes if it's an white space
int	ft_iswhitespace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

//check the bytes if it's an a an special character
int	ft_ispecial(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

//it skips till '\0' or whitespace or it counter another token
int	skip_quots(char *line, int *i)
{
	int	j;
	int	toggle;

	toggle = 1;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			if (toggle)
			{
				j = (*i);
				toggle = 0;
			}
			else if (line[*i] == line[j])
				toggle = 1;
		}
		else if ((ft_iswhitespace(line[*i]) || ft_ispecial(line[*i])) && toggle)
			break ;
		(*i)++;
	}
	if (toggle)
		return (1);
	return (0);
}

//count token in the string
int token_count(char *str)
{
	int	i;
	int	tcount;

	i = 0;
	tcount = 0;
	while (str[i])
	{
		while (ft_iswhitespace(str[i]))
			i++;
		if (!str[i])
			break ;
		if ((str[i] == '>' || str[i] == '<')
			&& (str[i + 1] == '>' || str[i + 1] == '<'))
			i += 2;
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i++;
		else
			if (!skip_quots(str, &i))
					return (ft_putendl_fd("non end quots", 2), -1);
		tcount++;
	}
	return (tcount);
}

// it fills the buffer that is given with and one of the token based on the token_id
void	fill_with_token(char **buffer, int token_id)
{
	if (token_id == PIPE)
		*buffer = ft_strdup("|");
	else if (token_id == IND)
		*buffer = ft_strdup("<");
	else if (token_id == OUD)
		*buffer = ft_strdup(">");
	else if (token_id == APP)
		*buffer = ft_strdup(">>");
	else if (token_id == HERDOC)
		*buffer = ft_strdup("<<");
	g_lst_addback(g_new_garbage(*buffer));
}

// just calls the regular ft_substr and add it's allocated memory it the linked list
char	*safe_substr(char *str, unsigned int start, size_t len)
{
	char	*pp;

	if (len)
	{
		pp = ft_substr(str, start, len);
		if (!pp)
			return (NULL);
		g_lst_addback(g_new_garbage(pp));
		return (pp);		
	}
	return (NULL);
}

// it handles the quote and return an allocated memory that doesnt contain those quotes
char	*handle_quote(char *line, int *i, int *mode)
{
	int	j;
	int	k;

	j = *i;
	k = 0;
	(*i)++;
	while (line[*i])
	{
		if (line[*i] == line[j])
		{
			(*i)++;
			return (safe_substr(line, j + 1, k));
		}
		else
			k++;
		(*i)++;
	}
	*mode = -1;
	return (NULL);
}

// this function breaks string line (input) into small strings that is tokenized 
char	*buffer_filler(char *line, int *i, int *mode)
{
	int	j;
	char	*str;

	str = NULL;
	while (ft_iswhitespace(line[*i]))
		(*i)++;
	while (line[*i])
	{
		if (ft_iswhitespace(line[*i]) || ft_ispecial(line[*i]))
			break ;
		else if (line[*i] == '\'' || line[*i] == '"')
			str = ft_gnl_strjoin(str, handle_quote(line, i, mode));
		else
		{
			j = *i;
			while (line[*i] && line[*i] != '\'' && line[*i] != '"'
				&& !ft_iswhitespace(line[*i]) && !ft_ispecial(line[*i]))
				(*i)++;
			str = ft_gnl_strjoin(str, safe_substr(line, j, *i - j));
		}
	}
	if (str)
		g_lst_addback(g_new_garbage(str));
	return (str);
}

// split 
char	**spliting_based_token(char *line)
{
	int		i;
	int		k;
	int		quote_status;
	char	**strs;

	i = 0;
	k = 0;
	strs = safe_alloc((token_count(line) + 1) * sizeof(char *), 0);
	if (!strs)
		return (NULL);
	while (line[i])
	{
		quote_status = 0;
		while(ft_iswhitespace(line[i]))
			i++;
		if (!line[i])
			break ;
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			fill_with_token(strs + k, whichtoken(line, &i));
			i++;
		}
		else
		{
			strs[k] = buffer_filler(line, &i, &quote_status);
			if (!strs[k])
				return (NULL);
		}
		k++;
	}
	return (strs);
}

// it creates an array of integers that contain token ids of the splited input 
bool	tokenize(void)
{
	int	i;

	i = 0;
	util()->a = safe_alloc(util()->t * sizeof(int), 1);
	if (!util()->a || !util()->s)
		return (perror("sheru:"), false);
	while (i < util()->t)
	{
		util()->a[i] = token_value(util()->s[i]);
		i++;
	}
	return (true);
}

void	print_token(char **strs, int *token_arr, int tcount)
{
	int	i;
	char	*tokens[] = {"PIPE", "IND", "OUD", "APP", "HERDOC", "WORD"};

	i = 0;
	while (i < tcount)
	{
		printf("the line[%d]: [%s] \n\tit's id is :%s\n", i, strs[i], tokens[token_arr[i]]);
		i++;
	}
}

bool	syntax_check(void)
{
	int	i;

	i = 0;
	while (i < util()->t)
	{
		if (util()->a[i] == PIPE && (i + 1 >= util()->t || !i))
			return (ft_putendl_fd("syntax error", 2), false);
		else if ((util()->a[i] == IND || util()->a[i] == OUD)
			&& (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		else if ((util()->a[i] == APP || util()->a[i] == HERDOC)
			&& (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		i++;
	}
	return (true);
}

int	cmd_count(char **strs, int *arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == IND || arr[i] == OUD
			|| arr[i] == APP || arr[i] == HERDOC)
			i++;
		else
			j++;
		i++;
	}
	return (j);
}

void	cmd_filler(char **strs, int *arr, char **buffer)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == IND || arr[i] == OUD 
			|| arr[i] == APP || arr[i] == HERDOC)
			i++;
		else
			buffer[j++] = strs[i];
		i++;
	}
}

void	cmd_flag_handle(char **strs, int *arr, t_data *node, int *mode)
{
	int	j;

	j = cmd_count(strs, arr);
	printf("cmd count %d\n", j);
	node->cmd = safe_alloc((j + 1) * sizeof(char *), 0);
	if (!node->cmd)
		exit (EXIT_FAILURE);
	cmd_filler(strs, arr, node->cmd);
	*mode = 0;
}

void	stor_redirections(int *arr, char **strs, t_files *file)
{
	int	j;
	int	p;
	int	i;

	j = 0;
	p = 0;
	i = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == APP || arr[i] == OUD)
		{
			file->outfile[j] = strs[i + 1];
			file->o_type[j] = arr[i];
			j++;
			i += 2;
		}
		else if (arr[i] == IND)
		{
			file->infile[p] = strs[i + 1];
			p++;
			i += 2;
		}
		else
			i++;
	}
}

void	make_a_file(int incount, int outcount, t_files *file)
{
	file->infile = safe_alloc((incount + 1) * sizeof(char *), 0);
	file->outfile = safe_alloc((outcount + 1) * sizeof(char *), 0);
	file->o_type = safe_alloc(outcount * sizeof(int), 0);
	if (!file->o_type || !file->outfile || !file->infile)
		exit(EXIT_FAILURE);
}

void	handle_redirections(int *arr, char **strs, t_files *file, int *mode)
{
	int	incount;
	int	outcount;
	int	i;

	incount = 0;
	outcount = 0;
	i = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == APP || arr[i] == OUD || arr[i] == IND)
		{
			if (arr[i] == IND)
				incount++;
			else
				outcount++;
			i += 2;
		}
		else
			i++;
	}
	make_a_file(incount, outcount, file);
	stor_redirections(arr, strs, file);
	*mode = 0;
}

t_data	*last_node(t_data *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

bool	stor_in_list(char **strs, int *arr, t_data **node)
{
	int		i;
	int		toggle;
	int		boggle;
	t_data	*tmp;

	i = 0;
	while (strs[i])
	{
		toggle = 1;
		boggle = 1;
		tmp = safe_alloc(sizeof(t_data), 0);
		if (!tmp)
			return (false);
		if (arr[i] == PIPE)
			i++;
		while (strs[i] && arr[i] != PIPE)
		{
			if (arr[i] == WORD && toggle)
				cmd_flag_handle(strs + i, arr + i, tmp, &toggle);
			else if ((arr[i] == APP || arr[i] == OUD || arr[i] == IND) && boggle)
				handle_redirections(arr + i, strs + i, &tmp->file, &boggle);
			i++;
		}
		if (!*node)
			*node = tmp;
		else
			last_node(*node)->next = tmp;
	}
	return (true);
}

void	print_data(t_data *inlist)
{
	int		i;
	int		j;

	j = 0;
	while (inlist)
	{
		i = 0;
		printf("===============node %d===============\n", j);
		printf("struct t_data\n{");
		printf("\t*cmd =");
		while (inlist->cmd && inlist->cmd[i])
			printf("  {%s},", inlist->cmd[i++]);
		printf("\n");
		// printf("*data[0] = %s\n", (*box())->data[0]);
		i = 0;
		printf("\tt_files.infile :");
		while (inlist->file.infile && inlist->file.infile[i])
			printf(" {%s},", inlist->file.infile[i++]);
		printf("\n");
		i = 0;
		printf("\tt_files.outfile :");
		while (inlist->file.outfile && inlist->file.outfile[i])
			printf(" {%s},", inlist->file.outfile[i++]);
		printf("\n");
		i = 0;
		printf("\tt_files.o_types :");
		while (inlist->file.outfile && inlist->file.outfile[i])
			printf(" {%d},", inlist->file.o_type[i++]);
		printf("\n");
		printf("}\tt_data");
		printf("\n==============================\n");
		inlist = inlist->next; 
		j++;	
	}
}

// it's start the lexure
void	begin_lexing(char *line)
{
	util()->t = token_count(line);
	if (util()->t < 0)
		return ;
	util()->s = spliting_based_token(line);
	*box() = NULL;
	if (!tokenize() || !syntax_check()
		|| !stor_in_list(util()->s, util()->a, box()))
		return ;
	print_data(*box());
}

int	main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		line = readline("sheru>");
		if (!line)
			return (clear_container(), 0);
		add_history(line);
		begin_lexing(line);
	}
	return (0);
}
