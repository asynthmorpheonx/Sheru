/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/11 00:50:09 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_data	**box(void)
{
	static t_data	*pp;

	return (&pp);
}

bool	**ambiguous_ptr(void)
{
	static bool	*ptr;

	return (&ptr);
}

bool	is_ifs(int c)
{
	char	*ptr;
	int		i;

	ptr = key_value("IFS");
	if (*ptr)
	{
		i = 0;
		while (ptr[i])
		{
			if (ptr[i] == c)
				return (true);
			i++;
		}
		return (false);
	}
	return (c == '\n' || c == '\t' || c == ' ');
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

t_ferror	*fetcher(void)
{
	static t_ferror	pp;

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

// checks for the syntex of input tokens
bool	syntax_check(void)
{
	int	i;

	i = 0;
	while (i < util()->t)
	{
		if (util()->a[i] == PIPE && (i + 1 >= util()->t || !i || util()->a[i - 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		else if ((util()->a[i] == IND || util()->a[i] == OUD) && (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		else if ((util()->a[i] == APP || util()->a[i] == HERDOC) && (i + 1 >= util()->t || util()->a[i + 1] != WORD))
			return (ft_putendl_fd("syntax error", 2), false);
		i++;
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
		if (inlist->ab_redir)
			printf("\n\tambiguous error {true}\n");
		else
			printf("\n\tambiguous error {false}\n");
		printf("\t*cmd =");
		while (inlist->cmd && inlist->cmd[i])
			printf("  {%s},", inlist->cmd[i++]);
		printf("\n");
		i = 0;
		printf("\tt_files.infile :");
		while (inlist->file.infile && inlist->file.infile[i])
			printf(" {%s},", inlist->file.infile[i++]);
		printf("\n");
		i = 0;
		printf("\tt_files.i_type :");
		while (inlist->file.infile && inlist->file.infile[i])
			printf(" {%d},", inlist->file.i_type[i++]);
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

// it return the value if the key is exist, or a "\0" if there no key that match that.
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
	return (free(tmp), "");
}

bool	check_value(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '\0')
		return (false);
	while (value[i])
	{
		if (is_ifs(value[i]))
			return (false);
		i++;
	}
	return (true);
}

void	full_expand(char **str, char *ptr)
{
	int	len;
	int	i;
	int	toggle;

	len = ft_strlen(*str);
	i = 0;
	toggle = 1;
	while (is_ifs(ptr[i]))
	{
		i++;
		toggle = 0;
	}
	while (ptr[i])
	{
		while (!is_ifs(ptr[i]))
		{
			len++;
			i++;
		}
		if (is_ifs(ptr[i]) && toggle)
			break ;
		i++;
	}
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
	if (fetcher()->full_exp && fetcher()->flage && !check_value(ptr))
	{
		fetcher()->error_id = AMBIGUOUS_REDIRECT;
		return (0);
	}
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

// it's that set the fetch struct into store previous token and type expansion(full/normal)
void	fetch_setter(bool mode, int i, bool is_full)
{
	if (mode)
	{
		if (i && util()->a[i - 1] <= PIPE)
			fetcher()->flage = true;
		fetcher()->full_exp = is_full;
	}
	else
	{
		fetcher()->flage = false;
		fetcher()->error_id = 0;
		fetcher()->full_exp = false;
	}
}

// it expand the char **s from the struct utils when it found '$'.
void	expansion_data(int i, int j, int to, int bo)
{
	int	pi;

	pi = 0;
	while (util()->s[i])
	{
		j = 0;
		to = 1;
		bo = 1;
		while (util()->a[i] == WORD && util()->s[i][j])
		{
			fetch_setter(RESET, 0, 0);
			if (util()->s[i][j] == '\'' && to)
				switch_toggles(&bo);
			else if (util()->s[i][j] == '"' && bo)
				switch_toggles(&to);
			else if ((!i || (i && util()->a[i - 1] != HERDOC)) && util()->s[i][j] == '$' && bo)
			{
				if (to)
					fetch_setter(SET, i, true);
				else
					fetch_setter(SET, i, false);
				j += expand_var(&util()->s[i], j);
				if (fetcher()->error_id == AMBIGUOUS_REDIRECT)
				{
					printf("i value %d\n", i);
					*ambiguous_ptr()[pi] = true;
					break ;
				}
			}
			j++;
		}
		i++;
	}
}

void	reset_data_box(void)
{
	t_data	*next;

	if (*box())
	{
		while (*box())
		{
			next = (*box())->next;
			delete_one(*box());
			*box() = next;
		}
		*box() = NULL;	
	}
}

void	reset_util_box(void)
{
	delete_one(util()->s);
	delete_one(util()->a);
	util()->a = 0;
	util()->s = 0;
	util()->t = 0;
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
		reset_data_box();
		if (!stor_in_list(util()->s, util()->a, box()))
			return ;
		reset_util_box();
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
