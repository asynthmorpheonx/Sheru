/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/07 16:18:15 by mel-mouh         ###   ########.fr       */
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
