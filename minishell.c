/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-mouh <mel-mouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/05/29 16:25:30 by mel-mouh         ###   ########.fr       */
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

void switch_toggles(int *toggle)
{
	if (*toggle)
		*toggle = 0;
	else
		*toggle = 1;
}

// it's function that set the fetch struct into store previous token and type expansion(full/normal)
void fetch_setter(bool mode, int i, bool is_full)
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
		fetcher()->error = false;
		fetcher()->full_exp = false;
	}
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

bool	*mask_joining(bool *o_mask, char *pre, char *suff)
{
	bool	*new_mask;
	int		index;
	int		i;

	i = 0;
	index = ft_strlen(pre);
	new_mask = safe_alloc(ft_strlen(suff) + index, 0);
	if (!new_mask)
		return (NULL);
	while (i < index)
	{
		new_mask[i] = o_mask[i];
		i++;
	}
	i = 0;
	while (suff[i])
	{
		new_mask[i + index] = true;
		i++;
	}
	delete_one(o_mask);
	return (new_mask);
}

// it extend the util().s and update the the array
void extend_key(int *index, int *start, char *value, int end)
{
	int		i;
	int		j;
	int		u;
	int		len;
	char	*tmp;
	char	**extnd;
	char	**dup;
	bool	**mask;
	int		*a_dup;

	i = 0;
	j = 0;
	u = 0;
	tmp = NULL;
	if (*start)
		tmp = ft_substr(util()->s[*index], 0, *start);
	extnd = ifs_split(value);
	if (!extnd)
		return ;
	if (*start && is_ifs(*value))
		len = lenght_both(extnd, util()->s);
	else
		len = lenght_both(extnd, util()->s) - 1;
	dup = safe_alloc((len + 1) * sizeof(char *), 0);
	a_dup = safe_alloc(len * sizeof(int), 0);
	mask = safe_alloc(len * sizeof(bool *), 0);
	if (!dup || !a_dup)
	{
		if (tmp)
			free(tmp);
		ult_exit();
	}
	while (i < *index)
	{
		dup[i] = util()->s[i];
		a_dup[i] = util()->a[i];
		mask[i] = util()->mask[i];
		i++;
	}
	if (tmp && !is_ifs(*value))
	{
		mask[i] = mask_joining(util()->mask[i], tmp, extnd[j]);
		dup[i] = safe_join(tmp, extnd[j]);
		a_dup[i] = WORD;
		j++;
		i++;
	}
	else if (tmp)
	{
		g_lst_addback(g_new_garbage(tmp));
		mask[i] = safe_alloc(ft_strlen(tmp), 0);
		ft_memset(mask[i], true, ft_strlen(tmp));
		dup[i++] = tmp;
		a_dup[i - 1] = WORD;
	}
	while (extnd[j])
	{
		dup[i] = extnd[j];
		a_dup[i] = WORD;
		mask[i] = safe_alloc(ft_strlen(extnd[j]), 0);
		ft_memset(mask[i], true, ft_strlen(extnd[j]));
		i++;
		j++;
	}
	u = ft_strlen(dup[i - 1]);
	if (util()->s[*index][end] && !ft_isalpha(util()->s[*index][end]))
		dup[i - 1] = safe_join(dup[i - 1], util()->s[*index] + end);
	*index = i - 1;
	*start = u;
	while (i < len)
	{
		dup[i] = util()->s[i - j + 1];
		a_dup[i] = util()->a[i - j + 1];
		mask[i] = util()->mask[i - j + 1];
		i++;
	}
	util()->s = dup;
	util()->a = a_dup;
	util()->mask = mask;
}

bool	*handle_masking(char *str, int start, int len)
{
	bool	*mask;

	mask = safe_alloc(ft_strlen(str), 0);
	if (!mask)
		ult_exit();
	while (str[start] && start <= len)
	{
		mask[start] = true;
		start++;
	}
	return (mask);
}

void	replace_key_to_value(int *ind, int *strt, int k_len, char *value)
{
	char	*dup;
	bool	*mask;
	int		var;

	dup = NULL;
	mask = NULL;
	if (*strt)
		dup = ft_substr(util()->s[*ind], 0, *strt);
	dup = ft_gnl_strjoin(dup, value);
	var = ft_strlen(dup);
	dup = safe_join(dup, util()->s[*ind] + k_len);
	delete_one(util()->s[*ind]);
	delete_one(util()->mask[*ind]);
	util()->s[*ind] = dup;
	util()->mask[*ind] = handle_masking(dup, *strt, ft_strlen(value));
	if (*value)
		*strt = ft_strlen(value);
}

bool	check_value(char *str)
{
	int	i;
	int	toggle;
	int	count;

	i = 0;
	toggle = 1;
	count = 0;
	if (str && !*str)
		return (false);
	while (str[i])
	{
		if (!is_ifs(str[i]) && toggle)
		{
			count++;
			toggle = 0;
			if (count >	1)
				return (false);
		}
		else if (is_ifs(str[i]))
			toggle = 1;
		i++;
	}
	if (!count)
		return (false);
	return (true);
}

// this function expand the key found in util().s[index] and return the index after the expand
void expand_value(int *index, int *start)
{
	char	*dup;
	char	*value;
	bool	status;
	int		i;

	i = key_len(util()->s[*index], *start + 1);
	dup = NULL;
	value = key_value(util()->s[*index] + *start + 1);
	status = check_value(value);
	if (fetcher()->flage && fetcher()->full_exp && !status)
		fetcher()->error = true;
	else if (*value && fetcher()->full_exp && !status)
		extend_key(index, start, value, i);
	else
		replace_key_to_value(index, start, i, value);
}

// TODO : handle quote removal and empty value of variable
void expansion_data(int i, int j, int to, int sto)
{
	while (util()->s[i])
	{
		j = 0;
		to = 1;
		sto = 1;
		while (util()->s[i] && util()->s[i][j] && util()->a[i] > 4)
		{
			fetch_setter(RESET, 0, 0);
			if (util()->s[i][j] == '\'' && to)
				switch_toggles(&sto);
			else if (util()->s[i][j] == '"' && sto)
				switch_toggles(&to);
			else if ((!i || (i && util()->a[i - 1] != HERDOC)) && util()->s[i][j] == '$' && sto)
			{
				fetch_setter(SET, i, false);
				if (to)
					fetch_setter(SET, i, true);
				expand_value(&i, &j);
				if (!fetcher()->error)
					continue;
				util()->a[i] = -1;
			}
			j++;
		}
		i++;
	}
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

bool	creat_mask(void)
{
	bool	**mask;
	int		i;
	
	i = 0;
	mask = safe_alloc(util()->t * sizeof(bool *), 0);
	if (!mask)
		ult_exit();
	while (util()->s[i])
	{
		if (util()->a[i] == WORD)
		{
			mask[i] = safe_alloc(ft_strlen(util()->s[i]), 0);
			if (!mask[i])
				ult_exit();
		}
		i++;
	}
	util()->mask = mask;
	return (true);
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
		print_data(*box());
	}
}

size_t	session_name_len(char *str)
{
	size_t	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	return (i);
}

char	*export_session(void)
{
	static char	*str;
	char	*ptr;

	if (!str)
	{
		ptr = key_value(SESSIO);
		str = safe_substr(ptr, 6, session_name_len(ptr + 6));
	}
	return (str);
}

// creat an customize shell prompt just to show the user [USER@SESSION]-[OS@SHELL_NAME]
char	*creat_prompt(void)
{
	char	*str;
	char	*user;
	char	*session;

	user = key_value(USR);
	session = export_session();
	str = NULL;
	if (!str && *session && *user)
	{
		if (*user)
			str = ft_strjoin(user, "@");
		if (*session)
			str = ft_gnl_strjoin(str, session);
		str = ft_gnl_strjoin(str, ":~$ ");
	}
	g_lst_addback(g_new_garbage(str));
	return (str);
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