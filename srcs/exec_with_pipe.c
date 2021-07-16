#include "minishell.h"

void	open_pipes(t_data *data, int tokens_count)
{
	int	i;

	i = 0;
	while (i <= tokens_count)
	{
		if (pipe(data->fd[i]) == -1)
		{
			error_handler("error with creating pipe", 1);
			exit(1);
		}
		i++;
	}
}

void	close_unused_fd_child(t_data *data, int i, int tokens_count)
{
	int	k;

	k = 0;
	while (k <= tokens_count)
	{
		if (i != k)
			close(data->fd[k][0]);
		if (i + 1 != k)
			close(data->fd[k][1]);
		k++;
	}
}

void	create_child(t_data *data, int tokens_count, pid_t *pid, char **tmp)
{
	int	i;

	i = 0;
	while (i < tokens_count)
	{
		pid[i] = fork();
		signal(SIGINT, SIG_DFL);
		if (pid[i] < 0)
		{
			error_handler("Error with creating process", 1);
			exit(1);
		}
		if (pid[i] == 0)
		{
			close_unused_fd_child(data, i, tokens_count);
			data->fd_out[0] = data->fd[i + 1][1];
			data->fd_in[0] = data->fd[i][0];
			split_and_exec(data, tmp[i]);
			close(data->fd[i][0]);
			close(data->fd[i + 1][1]);
			exit(0);
		}
		i++;
	}
}

void 	close_unsed_fd_parent(t_data *data, int tokens_count)
{
	int	k;

	k = 0;
	while (k <= tokens_count)
	{
		if (k != tokens_count)
			close(data->fd[k][0]);
		close(data->fd[k][1]);
		k++;
	}
}

void	exec_cmd_line_with_pipes(t_data *data, char **tmp, int tokens_count)
{
	pid_t	*pid;
	int		status;
	char	c;
	char	*line_read;
	int		i;

	line_read = NULL;
	malloc_things(data, &pid, tokens_count);
	open_pipes(data, tokens_count);
	create_child(data, tokens_count, pid, tmp);
	close_unsed_fd_parent(data, tokens_count);
	i = 0;
	while (i < tokens_count)
	{
		wait(&status);
		signal(SIGINT, ctrl_c);
		i++;
	}
	while (read(data->fd[tokens_count][0], &c, 1) != 0)
		make_string(&line_read, c);
	close(data->fd[tokens_count][1]);
	ft_putstr_fd(line_read, STDOUT_FILENO);
	free_things(data, pid, tokens_count);
}