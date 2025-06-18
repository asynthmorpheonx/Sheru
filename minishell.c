/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoel-mos <hoel-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:38:01 by mel-mouh          #+#    #+#             */
/*   Updated: 2025/06/18 16:55:56 by hoel-mos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_shell.h>

t_data **box(void)
{
	static t_data *pp;

	return (&pp);
}

t_prstat	*process_status(void)
{
	static t_prstat	var;

	return (&var);
}

char	*exit_code(void)
{
	static char	exit_status[4];

	return (exit_status);
}

// this fn takes the paramter and storing int the $? as string it handles the overflow like the bash did
void	code_setter(int	new_code)
{
	int	i;

	i = 0;
	new_code = (new_code % 256 + 256) % 256;
	if (new_code < 9)
		i = 0;
	else if (new_code < 99)
		i = 1;
	else
		i = 2;
	exit_code()[i + 1] = '\0';
	if (!new_code)
		exit_code()[0] = 48;
	else
	{
		while (new_code)
		{
			exit_code()[i] = new_code % 10 + '0';
			i--;
			new_code /= 10;
		}		
	}
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

t_env **envp(void)
{
	static t_env *pp;

	return (&pp);
}

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
			ult_exit();
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
		ult_exit();
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
		printf("\tt_file.infile :");
		while (inlist->file.infile && inlist->file.infile[i])
			printf(" {%s},", inlist->file.infile[i++]);
		printf("\n");
		i = 0;
		printf("\tt_file.i_type :");
		while (inlist->file.infile && inlist->file.infile[i])
			printf(" {%d},", inlist->file.i_type[i++]);
		printf("\n");
		i = 0;
		printf("\tt_file.outfile :");
		while (inlist->file.outfile && inlist->file.outfile[i])
			printf(" {%s},", inlist->file.outfile[i++]);
		printf("\n");
		i = 0;
		printf("\tt_file.o_types :");
		while (inlist->file.outfile && inlist->file.outfile[i])
			printf(" {%d},", inlist->file.o_type[i++]);
		printf("\n");
		printf("}\tt_data");
		printf("\n==============================\n");
		inlist = inlist->next;
		j++;
	}
}

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
	t_env *pp;
	char *tmp;
	int i;

	if (key[0] == '$' || !key[0])
		return ("");
	else if (key[0] == '?')
		return (exit_code());
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

void reset_util_box(void)
{
	if (util()->s)
		delete_one(util()->s);
	if (util()->a)
		delete_one(util()->a);
	if (util()->mask)
		delete_one(util()->mask);
	util()->herdoc = 0;
	ft_bzero(util()->ports, 16 * sizeof(int));
	util()->t = 0;
}

void	expand_herdoc_data(char *str, int fd)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			tmp = key_value(str + i + 1);
			len = key_len(str + i, 0);
			if (str[i + 1] == '?')
				len++;
			if (*tmp)
				write(fd, tmp, ft_strlen(tmp));
			i += len;
		}
		else
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}

void	here_doc_util(char *input, int fd)
{
	if (util()->herdoc_exp)
		expand_herdoc_data(input, fd);
	else if (*input)
		write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

void	safe_pipe(int *fds)
{
	if (pipe(fds) == -1)
	{
		perror("pipe");
		ult_exit();
	}
}

void	close_herdoc_ports(void)
{
	int	i;

	i = 0;
	while (util()->ports[i] != 0)
	{
		close(util()->ports[i]);
		i++;
	}
}

char	*here_doc_reader(char *str, bool mode, int i)
{
	char	*input;
	int		fds[2];

	input = NULL;
	if (mode)
		safe_pipe(fds);
	*process_status() = HERDOC_READ;
	while (1)
	{
		input = readline("> ");
		if (*process_status() == INTERRUPTED
			|| !input || !ft_memcmp(input, str, ft_strlen(input) + 1))
			break;
		if (mode)
			here_doc_util(input, fds[1]);
		free(input);
		input = NULL;
	}
	if (mode)
		close(fds[1]);
	if (mode)
	{
		util()->ports[i] = fds[0];
		return (ft_itoa(fds[0]));
	}
	return (NULL);
}

void	replace_fd(t_data *node, char *str, int i)
{
	delete_one(node->file.infile[i]);
	node->file.infile[i] = str;
	g_lst_addback(g_new_garbage(str));
}

void	herdoc_job(void)
{
	int		i;
	char	*str;
	t_data	*tmp;
	int		ind;

	i = 0;
	ind = 0;
	tmp = *box();
	while (tmp)
	{
		while (tmp->file.infile && tmp->file.infile[i])
		{
			if (tmp->file.i_type[i] == HERDOC && tmp->file.infile[i + 1])
				here_doc_reader(tmp->file.infile[i], false, ind);
			else if (tmp->file.i_type[i] == HERDOC)
			{
				str = here_doc_reader(tmp->file.infile[i], true, ind);
				if (str)
					replace_fd(tmp, str, i);
				ind++;
			}
			if (*process_status() == INTERRUPTED)
				return (close_herdoc_ports());
			i++;
		}
		i = 0;
		tmp = tmp->next;
	}
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
		if (util()->herdoc)
			herdoc_job();
		if (*process_status() != INTERRUPTED)
			execute_command(*box());
		reset_util_box();
	}
}

void	interupt_handle(int	sig_num)
{
	if (sig_num == SIGINT && *process_status() != INTERRUPTED)
	{
		if (*process_status() == HERDOC_READ)
		{
			*process_status() = INTERRUPTED;
			rl_done = 1;
		}
		else
			write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		code_setter(130);
	}
}

int main(int ac, char **av, char **env)
{
	char	*line;

	(void)ac;
	(void)av;
	signal(SIGINT, interupt_handle);
	make_env(env, envp(), 0, 0);
	code_setter(0);
	while (1)
	{
		*process_status() = SCANIN;
		line = readline(creat_prompt());
		if (!line)
		{
			write(1, "exit\n", 5);
			return (clear_container(), 0);
		}
		if (*line)
		{
			add_history(line);
			begin_lexing(line);
		}
	}
}
