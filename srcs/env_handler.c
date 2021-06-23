#include "minishell.h"

int 	env_key_finder(char **env, char *env_key)
{
	int		i;
	int		k;
	char	*current_key;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], env_key, ft_strlen(env_key)))
		{
			k = 0;
			while (env[i][k] != '=')
				k++;
			current_key = ft_substr(env[i], 0, k);
			if (!ft_strncmp(env_key, current_key, ft_strlen(current_key)))
			{
				free(env_key);
				free(current_key);
				return (i);
			}
		}
		i++;
	}
	return (-1);
}

char	*key_not_found(char *str, int start, int end)
{
	char	*before_variable;
	char	*new_str;

	before_variable = ft_substr(str, 0, start);
	new_str = ft_strjoin(before_variable, str + end);
	if (before_variable)
		free(before_variable);
	return (new_str);
}

char 	*key_found(char *env_str, char *str, int start, int end)
{
	char	*env_value;
	char 	*new_str;
	char 	*merge_str;
	int		i;

	i = 0;
	while (env_str[i] != '=')
		i++;
	env_value = ft_substr(env_str, i + 1, ft_strlen(env_str) - i);
	new_str = ft_substr(str, 0, start);
	merge_str = ft_strjoin(new_str, env_value);
	if (new_str)
		free(new_str);
	if (env_value)
		free(env_value);
	new_str = ft_strjoin(merge_str, str + end);
	if (merge_str)
		free(merge_str);
	return (new_str);
}

char	*env_handler(char *str, int *i, char **env)
{
	char	*env_key;
	char	*new_str;
	int		start;
	int		line_number;

	start = *i;
	(*i)++;
	while (str[*i] == '_' || ft_isalnum(str[*i]))
		(*i)++;
	env_key = ft_substr(str, start + 1, *i - start - 1);
	if ((line_number = env_key_finder(env, env_key)) == -1)
		new_str = key_not_found(str, start, *i);
	else
		new_str = key_found(env[line_number], str, start, *i);
	return (new_str);
}