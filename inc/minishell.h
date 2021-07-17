#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include <sys/termios.h>

int	exit_status;

typedef struct s_data
{
	//вся введенная строка:
	char	*line_read;
	//массив строк - команды и аргументы:
	char	**cmd_lines;
	//тут храним фд вывода [0] - открытый файл [1] - копия STDOUT
	int		fd_out[2];
	//тут храним фд ввода - открытый файл [1] - копия STDOUT
	int 	fd_in[2];
	int		**fd;
	//переменные окружения из main()
	char	**envp;
	char	**envp_exp;
	struct termios config;
}				t_data;

void	parsing(t_data *data);
void	exec_commands(t_data *data);
void	error_handler(char *str, int exit_status);
int		check_syntax(char *str);
void	spec_sym_handler(char **str, t_data *data);
char	*env_handler(char *str, int *i, char **envp);
int		closed_quotes(char *str, int i, char qs);
char	**split_line(char *str);
void	malloc_word(char *str, int *i, char **split_string, char s);
int		char_count(char *str, int *i, char s);
void	copy_space_word(char *str, int *i, char **split_string);
void 	copy_word(char *str, int *i, char **split_string, char s);
int		command_line_count(char *str);
void	line_char_count(char *str, int *i);
int		not_qs_char_count(char *str, int *i);
int		redirect_handler(char **str, t_data *data);
char	*dquotes_handler(char *str, int *i, t_data *data);
void	skip_other(char *str, int *i);
char	*make_filename(char *str, int i, t_data *data);
char	*readline_history(char *prompt, char *line_read, t_data *data);
void	remove_redirect(char **str, int *i, char c);
int 	app_redirect(char *str, int i, t_data *data);
int		redirect(char *str, int i, t_data *data);
char	*string_join(char *str1, char *str2);
int 	heredoc_read(t_data *data, char *word);
void	ctrl_c(int sig);
void	split_and_exec(t_data * data, char *cmd_line);
char	**split_by_pipe(char *str);
void	make_string(char **str, char c);
void	exec_cmd_line_with_pipes(t_data *data, char **tmp, int tokens_count);
void	malloc_things(t_data *data, pid_t **pid, int tokens_count);
void	free_things(t_data *data, pid_t *pid, int tokens_count);
void	reset_fd_to_default(t_data *data);
void	ctrl_c_herdoc(int sig);
void	ctrl_d(t_data *data);
void	ctrl_c(int sig);
void	ctrl_c_child(int sig);
int 	empty_line(char *str);
/*
** builtins
*/

int		echo(char **cmd_line);
int 	cd(char **cmd_line, t_data *data);
int		pwd();
int		export(char **cmd_line, t_data *data);
int		unset(char **cmd_line, t_data *data);
int		env(t_data *data);
void 	exit_minishell();

/*
** not builtins
*/

int 	strings_counter(char **array);
void	execute_bin(char **cmd_line, t_data *data);
int		find_env_var(char *key, char **env_vars);
char 	**copy_envp(char **envp);
char	**join_str_to_arr(char **old_arr, char *str);
char	*get_minishell_env(char *key, char **env_vars);
void	add_env_var(t_data *data, char *cmd_line);
int		check_and_change_env_vars(char *cmd_line, t_data *data);
char	*str_3_join(char const *s1, char const *s2, char const *s3);

#endif
