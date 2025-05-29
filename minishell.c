/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/29 22:04:58 by mel-mouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_data **box(void)
{
	static t_data *pp;

	return (&pp);
}

bool **ambiguous_ptr(void)
{
	static bool *ptr;

	return (&ptr);
}

bool is_ifs(int c)
{
	char *ptr;
	int i;

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

void ult_exit(void)
{
	clear_container();
	exit(EXIT_FAILURE);
}

t_envp **envp(void)
{
	static t_envp *pp;

	return (&pp);
}

//
t_ferror *fetcher(void)
{
	static t_ferror pp;

	return (&pp);
}

t_utils *util(void)
{
	static t_utils pp;

	return (&pp);
}

// checks the bytes if it's an white space
int ft_iswhitespace(int c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

// check the bytes if it's an a an special character
int ft_ispecial(int c)
{
	return (c == '|' || c == '>' || c == '<');
}

// just calls the regular ft_substr and add it's allocated memory it the linked list
char *safe_substr(char *str, unsigned int start, size_t len)
{
	char *pp;

	if (len)
	{
		pp = ft_substr(str, start, len);
		if (!pp)
		{
			clear_container();
			exit(EXIT_FAILURE);
		}
		g_lst_addback(g_new_garbage(pp));
		return (pp);
	}
	return (NULL);
}

char *safe_join(char *s1, char *s2)
{
	char *pp;

	pp = ft_strjoin(s1, s2);
	if (!pp)
	{
		clear_container();
		exit(EXIT_FAILURE);
	}
	delete_one(s1);
	g_lst_addback(g_new_garbage(pp));
	return (pp);
}

// checks for the syntex of input tokens
bool syntax_check(void)
{
	int i;

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

void print_data(t_data *inlist)
{
	int i;
	int j;

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

// hadi azbi hia li kat7sb 
int key_len(char *str, int pos)
{
	int i;

	i = pos + 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

// it return the value if the key is exist, or a "\0" if there no key that match that.
char *key_value(char *key)
{
	t_envp *pp;
	char *tmp;
	int i;

	if (key[0] == '$' || !key[0])
		return ("");
	i = key_len(key, 0);
	pp = *envp();
	tmp = ft_substr(key, 0, i);
	if (!tmp)
		ult_exit();
	while (pp)
	{
		if (!ft_memcmp(pp->key, tmp, i + 1))
			return (free(tmp), pp->value);
		pp = pp->next;
	}
	return (free(tmp), "");
}

int lenght_both(char **s1, char **s2)
{
	int i;
	int len;

	i = 0;
	while (s1 && s1[i])
		i++;
	len = i;
	i = 0;
	while (s2 && s2[i])
		i++;
	len += i;
	return (len);
}

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

void reset_data_box(void)
{
	t_data *next;

	if (*box())
	{
		next = *box();
		clean_lst((*box())->cmd);
		while (*box())
		{
			next = (*box())->next;
			delete_one(*box());
			*box() = next;
		}
	}
}

void reset_util_box(void)
{
	delete_one(util()->s);
	delete_one(util()->a);
	delete_one(util()->mask);
	util()->herdoc = 0;
	util()->t = 0;
}

// it's start the lexure
void begin_lexing(char *line)
{
	reset_data_box();
	if (!token_count(line))
		return;
	util()->s = spliting_based_token(line);
	if (tokenize() && syntax_check())
	{
		if (util()->herdoc > 16)
		{
			ft_putendl_fd("maximum here-document count exceeded", 2);
			clear_container();
			exit(2);
		}
		creat_mask();
		expansion_data(0, 0, 1, 1);
		handle_quote();
		if (!stor_in_list(util()->s, util()->a, box()))
			return;
		reset_util_box();
		// TODO: HANDLE OPENING HERDOCS
		print_data(*box());
	}
}

int main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;

	line = NULL;
	(void)ac;
	(void)av;
	make_env(env, envp(), 0, 0);
	prompt = creat_prompt();
	if (!prompt)
		ult_exit();
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			write(1, "exit\n", 5);
			return (clear_container(), 0);
		}
		add_history(line);
		begin_lexing(line);
	}
}