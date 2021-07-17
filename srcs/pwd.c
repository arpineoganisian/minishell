#include "minishell.h"

int pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		error_handler(strerror(errno), 1);
//		ft_putendl_fd(strerror(errno), 2);
		return 1;
	}
	else
	{
		ft_putendl_fd(pwd, STDOUT_FILENO);
	 	free(pwd);
	}
	return 0;
}