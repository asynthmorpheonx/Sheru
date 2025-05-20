#include "minishell.h"

int	check_char(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

void print_error(char *msg)
{
	printf("export: `%s`: not a valid identifier\n", msg);
	// handle error | call garbage
	return ;
}
void	check_var(char *container, int *value_start, t_export *data)
{
	int	(i);
	if (check_char(container[0]) != 1)
		print_error(container);
	i = 0;
	while (container[i] && container[i] != '=')
	{
		if (container[i] == '+')
		{
			if (container[i + 1] == '=')
			{
				*value_start = i + 1;
				data->export_check = true;
				break ;
			}
			else
				print_error(container);
		}
		else if (!check_char(container[i]))
			print_error(container);
		i++;
	}
	if (!*value_start)
		*value_start = i;
}

char	*get_buffs(char *container, int start, int limit)
{
	int		i;
	char	*buff;

	i = start;
	if (limit)
	{
		while (container[i] && container[i] != limit)
			i++;
		buff = safe_alloc(i - start + 1, 0);
		i = 0;
		while (container[start] && container[start] != limit)
			buff[i++] = container[start++];
		buff[i] = '\0';
	}
	else
	{
		while (container[i])
			i++;
		buff = safe_alloc(i - start + 1, 0);
		i = 0;
		while (container[start])
			buff[i++] = container[start++];
		buff[i] = '\0';
	}
	return (buff);
}

void	build_export_data(t_data *cmd_list, char *container)
{
	t_export	*data;
	int			u;
	
	char *(var), *(value), (delimiter);
	u = 0;
	cmd_list->export_data = safe_alloc(sizeof(t_export), 0);
	data = cmd_list->export_data;
	data->export_check = false;
	check_var(container, &u, data);
	if(data->export_check)
		delimiter = '+';
	else
		delimiter = '=';
	var = get_buffs(container, 0, delimiter);
	value = get_buffs(container, ++u, 0);
	data->export_var = var;
	if (data->export_check)
		data->export_appe = value;
	else
		data->export_value = value;
}