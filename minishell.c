/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/06 22:11:54 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

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

void	count_in_out(int *in, int *out, int *arr, char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && arr[i] != PIPE)
	{
		if (arr[i] == APP || arr[i] == OUD || arr[i] == IND)
		{
			if (arr[i] == IND)
				(*in)++;
			else
				(*out)++;
			i += 2;
		}
		else
			i++;
	}
}

void	handle_redirections(int *arr, char **strs, t_files *file, int *mode)
{
	int	incount;
	int	outcount;

	incount = 0;
	outcount = 0;
	count_in_out(&incount, &outcount, arr, strs);
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
				i++;
				continue;
			}
			else if ((arr[i] == APP || arr[i] == OUD || arr[i] == IND) && bo)
				handle_redirections(arr + i, strs + i, &tmp->file, &bo);
			else if (arr[i] == HERDOC && zo)
				tmp->her_doc = heredoc_heandler(strs + i, arr + i, &zo);
			i += 2;
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
	char	*tmp;
	int		i;

	if (key[0] == '$' || !key[0])
		return ("\0");
	i = 0;
	pp = *envp();
	while (key[i] && !ft_iswhitespace(key[i])
		&& (ft_isalpha(key[i]) || key[i] == '_'))
		i++;
	tmp = ft_substr(key, 0, i);
	if (!tmp)
		ult_exit();
	while (pp)
	{
		if (!ft_strncmp(pp->key, tmp, i))
			return (free(tmp), pp->value);
		pp = pp->next;
	}
	return (free(tmp), "\0");
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
