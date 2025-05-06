/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/06 14:36:26 by mel-mouh         ###   ########.fr       */
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

void	ult_exit(void)
{
	clear_container();
	exit (EXIT_FAILURE);
}

t_envp	**envp(void)
{
	static t_envp	*pp;

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
bool token_count(char *str)
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
			&& (str[i + 1] == str[i]))
			i += 2;
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i++;
		else
			if (!skip_quots(str, &i))
				return (ft_putendl_fd("non end quots", 2), false);
		tcount++;
	}
	util()->t = tcount;
	return (true);
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
		{
			clear_container();
			exit (EXIT_FAILURE);
		}
		g_lst_addback(g_new_garbage(pp));
		return (pp);		
	}
	return (NULL);
}

char	*safe_join(char *s1, char *s2)
{
	char	*pp;

	pp = ft_gnl_strjoin(s1, s2);
	if (!pp)
	{
		clear_container();
		exit (EXIT_FAILURE);
	}
	g_lst_addback(g_new_garbage(pp));
	return (pp);
}

// this function breaks string line (input) into small strings that is tokenized 
char	*buffer_filler(char *s, int *i)
{
	int		j;
	int		q;
	char	*str;

	while (ft_iswhitespace(s[*i]))
		(*i)++;
	q = -1;
	j = *i;
	while (s[*i])
	{
		if (q == -1 && (ft_iswhitespace(s[*i]) || ft_ispecial(s[*i])))
			break ;
		else if (s[*i] == '\'' || s[*i] == '"')
		{
			if (q == -1)
				q = *i;
			else if (q >= 0 && s[*i] == s[q])
				q = -1;			
		}
		(*i)++;
	}
	str = safe_substr(s, j, *i - j);
	return (str);
}

// split 
char	**spliting_based_token(char *line)
{
	int		i;
	int		k;
	char	**strs;

	i = 0;
	k = 0;
	strs = safe_alloc((util()->t + 1) * sizeof(char *), 0);
	if (!strs)
		exit (EXIT_FAILURE);
	while (line[i])
	{
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
			strs[k] = buffer_filler(line, &i);
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
	// for (int i = 0; i < util()->t; i++)
	// 	printf("==============++++> %d\n", util()->a[i]);
	return (true);
}

bool	syntax_check(void)
{
	int	i;

	i = 0;
	while (i < util()->t)
	{
		if (util()->a[i] == PIPE && (i + 1 >= util()->t || !i || util()->a[i + 1] != WORD || util()->a[i - 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		else if ((util()->a[i] == IND || util()->a[i] == OUD) && (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		else if ((util()->a[i] == APP || util()->a[i] == HERDOC) && (i + 1 >= util()->t || util()->a[i + 1] != WORD))
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

void	store_in_tdata(t_data **node, t_data *tmp)
{
	if (!*node)
		*node = tmp;
	else
		last_node(*node)->next = tmp;
}

char	**heredoc_heandler(char **str, int *arr, int *mode)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = 0;
	while (str[i] && arr[i] != PIPE)
	{
		if (arr[i] == HERDOC)
		{
			j++;
			i += 2;
		}
		else
			i++;
	}
	if (j == 0 || j > 16)
	{
		if (j > 16)
			ft_putendl_fd("maximum here-document count exceeded", 2);
		return (NULL);
	}
	printf("------------------___>%d\n", j);
	buff = safe_alloc((j + 1) * sizeof(char *), 0);
	if (!buff)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && arr[i] != PIPE)
	{
		if (arr[i] == HERDOC)
		{
			buff[j++] = str[i + 1];
			i += 2;
		}
		else
			i++;
	}
	printf("=========================>%s\n", *buff);
	*mode = 0;
	return (buff);
}

// fix this asi zbi i kaidkhl line word secion fach kaikon non word
// it store the char **strs in linked-list.
bool	stor_in_list(char **strs, int *arr, t_data **node)
{
	int		i;
	int		to;
	int		bo;
	int		zo;
	t_data	*tmp;

	i = 0;
	while (strs[i])
	{
		to = 1;
		bo = 1;
		zo = 1;
		tmp = safe_alloc(sizeof(t_data), 0);
		if (!tmp)
			return (false);
		if (arr[i] == PIPE)
			i++;
		while (strs[i] && arr[i] != PIPE)
		{
			if (arr[i] == WORD)
			{
				if (to)
					cmd_flag_handle(strs + i, arr + i, tmp, &to);
			}
			else if (arr[i] == APP || arr[i] == OUD || arr[i] == IND)
			{
				if (bo)
					handle_redirections(arr + i, strs + i, &tmp->file, &bo);
				i++;
			}
			else if (arr[i] == HERDOC)
			{
				if (zo)
					tmp->her_doc = heredoc_heandler(strs + i, arr + i, &zo);
				i++;
			}
			i++;
		}
		store_in_tdata(node, tmp);
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
		i = 0;
		printf("\t*here_doc :");
		while (inlist->her_doc && inlist->her_doc[i])
			printf(" {%s},", inlist->her_doc[i++]);
		printf("\n");
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

// it return the value if the key is exist, or a "\0" if there no ket that match that.
char	*key_value(char *key)
{
	t_envp	*pp;
	int		i;
	char	*tmp;

	if (key[0] == '$' || !key[0])
		return ("\0");
	i = 0;
	pp = *envp();
	while (key[i] && !ft_iswhitespace(key[i]) && (ft_isalpha(key[i]) || key[i] == '_'))
		i++;
	tmp = ft_substr(key, 0, i);
	if (!tmp)
		ult_exit();
	printf("______________________________>[%s]\n", tmp);
	while (pp)
	{
		if (!ft_strncmp(pp->key, tmp, i))
		{
			free(tmp);
			return (pp->value);
		}
		pp = pp->next;
	}
	free(tmp);
	return ("\0");
}

// saraha this the one that expand the *str a fia ktrt lhadra.
int	expand_var(char **str, int start)
{
	char	*dup;
	char	*ptr;
	char	*tmp;
	int		j;

	j = start + 1;
	dup = NULL;
	while ((*str)[j] && (ft_isalpha((*str)[j]) || (*str)[j] == '_'))
		j++;
	if (start)
		dup = ft_substr(*str, 0, start);
	ptr = key_value(*str + start + 1);
	tmp = ft_gnl_strjoin(dup, ptr);
	dup = safe_join(tmp, *str + j);
	delete_one(*str);
	*str = dup;
	if (!*ptr)
		return (start);
	return (j);
}

void	switch_toggles(int *toggle)
{
	if (*toggle)
		*toggle = 0;
	else
		*toggle = 1;
}

// it expand the char **s from the struct utils when it found '$'.
void	expansion_data(int i, int j, int to, int bo)
{
	while (util()->s[i])
	{
		j = 0;
		to = 1;
		bo = 1;
		while (util()->s[i][j])
		{
			if (util()->s[i][j] == '\'' && to)
				switch_toggles(&bo);
			else if (util()->s[i][j] == '"' && bo)
				switch_toggles(&to);
			else if (util()->s[i][j] == '$' && bo)
				j += expand_var(&util()->s[i], j);
			j++;
		}
		i++;
	}
}

// it returns count of byts but the closed quotes execluded.
size_t	size_quot(char *str)
{
	size_t	i;
	size_t	k;
	int		j;

	i = 0;
	j = -1;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (j == -1)
				j = i;
			else if (j >= 0 && str[j] == str[i])
			{
				j = -1;
				k += 2;
			}
		}
		i++;
	}
	return (i - k);
}

// this function the something that i cant explain.
void	remove_quote(size_t len, char **str, int i, int j)
{
	char	*ptr;
	int		q;

	q = -1;
	ptr = safe_alloc((len + 1) * sizeof(char), 0);
	if (!ptr)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '\'' || (*str)[i] == '"')
		{
			if (q == -1 || (*str)[q] == (*str)[i])
			{
				if (q == -1)
					q = i;
				else
					q = -1;
				i++;
				continue ;
			}
		}
		ptr[j++] = (*str)[i++];
	}
	delete_one(*str);
	*str = ptr;
}

//this function recreate the string data for handling quote
void	handle_quote(void)
{
	int		i;
	size_t	len;

	i = 0;
	while (util()->s[i])
	{
		len = size_quot(util()->s[i]);
		if (util()->a[i] == WORD && ft_strlen(util()->s[i]) != len)
			remove_quote(len, &util()->s[i], 0, 0);
		i++;
	}
}

// it's start the lexure
void	begin_lexing(char *line)
{
	if (!token_count(line))
		return ;
	util()->s = spliting_based_token(line);
	if (tokenize() && syntax_check())
	{
		expansion_data(0, 0, 1, 1);
		handle_quote();
		*box() = NULL;
		if (!stor_in_list(util()->s, util()->a, box()))
			return ;
		print_data(*box());		
	}
}

// it returns pointer the last node in the list "lst".
t_envp	*last_env(t_envp *lst)
{
	while (lst->next)
		lst = lst->next;
	return (lst);
}

// it just adds the node *tmp to the linked list **lst.
void	add_to_envp(t_envp **lst, t_envp *tmp)
{
	if (!*lst)
		*lst = tmp;
	else
		last_env(*lst)->next = tmp;
}

// it stores char **envp into and linked list-list with memebers key, value for each node.
	void	make_env(char **env, t_envp **lst, int i, int j)
	{
		int		toggle;
		t_envp	*tmp;

		while (env[i])
		{
			j = 0;
			toggle = 1;
			tmp = safe_alloc(sizeof(t_envp), 0);
			if (!tmp)
				exit (EXIT_FAILURE);
			while(env[i][j])
			{
				if (env[i][j] == '=' && toggle)
				{
					tmp->key = safe_substr(env[i], 0, j);
					tmp->value = safe_substr
					(env[i], j + 1, ft_strlen(env[i] + j + 1));
					toggle = 0;
				}
				j++;
			}
			add_to_envp(lst, tmp);
			i++;
		}
	}

int	main(int ac, char **av, char **env)
{
	char *line;

	line = NULL;
	(void)ac;
	(void)av;
	make_env(env, envp(), 0, 0);
	while (1)
	{
		line = readline("sheru>");
		if (!line)
		{
			write(1, "exit\n", 5);
			return (clear_container(), 0);
		}
		add_history(line);
		begin_lexing(line);
	}
	return (0);
}
