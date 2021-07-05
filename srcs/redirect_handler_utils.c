#include "minishell.h"

char	*make_filename(char *str, int i)
{
	int		tmp;
	char	*tmp_str;

	if (str[i] == '\"' && closed_quotes(str, i, '\"'))
	{
		tmp = i;
		while (str[++i] != '\"')
			;
	}
	else if (str[i] == '\'' && closed_quotes(str, i, '\''))
	{
		tmp = i;
		while (str[++i] != '\'')
			;
	}
	else
	{
		tmp = i;
		while (str[++i] != ' ' && str[i])
			;
	}
	tmp_str = ft_substr(str, tmp, i - tmp + 1);
	spec_sym_handler(&tmp_str);
	return (tmp_str);
}

void	skip_other(char *str, int *i)
{
	while (str[*i] != '>' && str[*i])
	{
		if (str[*i] == '\'' && closed_quotes(str, *i, '\''))
		{
			(*i)++;
			while (str[*i] != '\'' && str[*i])
				(*i)++;
		}
		if (str[*i] == '\"' && closed_quotes(str, *i, '\"'))
		{
			(*i)++;
			while (str[*i] != '\"' && str[*i])
				(*i)++;
		}
		if (str[*i])
			(*i)++;
	}
}

void	remove_redirect(char **str, int *i, char c)
{
	char	*new_str;
	char	*first_part;
	int		start;

	start = *i;
	while ((*str)[*i] == c)
		(*i)++;
	while ((*str)[*i] == ' ')
		(*i)++;
	if ((*str)[*i] == '\"' && closed_quotes(*str, *i, '\"'))
		while ((*str)[++(*i)] != '\"')
			;
	else if ((*str)[*i] == '\'' && closed_quotes(*str, *i, '\''))
		while ((*str)[++(*i)] != '\'')
			;
	else
		while ((*str)[++(*i)] != ' ' && (*str)[*i])
			;
	first_part = ft_substr(*str, 0, start);
	new_str = ft_strjoin(first_part, *str + *i + 1);
	free(first_part);
	free(*str);
	*str = ft_strdup(new_str);
	free(new_str);
	*i = start;
}

int	redirect(char *str, int i, t_data *data)
{
	char	*filename;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i);
	data->fd_out = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	free(filename);
	if (data->fd_out == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}

int 	app_redirect(char *str, int i, t_data *data)
{
	char	*filename;

	while (str[i] == ' ')
		i++;
	filename = make_filename(str, i);
	data->fd_out = open(filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	free(filename);
	if (data->fd_out == -1)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (1);
	}
	return (0);
}