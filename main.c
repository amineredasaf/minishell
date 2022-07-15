#include "minishell.h"

char	*ft_trim(char *str)
{
	int		i;
	char	*result = NULL;
	int		j;
	int		end;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while(str[i] == ' ')
		i++;
	if (str[i])
	{
		while (str[i])
		{
			j++;
			i++;
		}
		i--;
		while (str[i] == ' ')
		{
			i--;
			j++;
		}
		end = i;
		result = malloc (j + 1);
		i = 0;
		j = 0;
		while (str[i] == ' ')
			i++;
		while (i <= end)
		{
			result[j] = str[i];
			i++;
			j++;
		}
		result[j] = '\0';
		free(str);
		return (result);
	}
	return (str);
}

void	ft_delete_quotes(t_data *data)


int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data.ac = argc;
	data.av = argv;
	data.env = env;
	data.first_export = NULL;
	ft_env(&data);
	while (69)
	{
		data.lst_lexer = NULL;
		data.lst_cmd = NULL;
		data.error = 0;
		data.cmd = readline("minishell-1.0 > ");
		if (!data.cmd || !strcmp(data.cmd, "exit"))
			exit(1);
		if (data.cmd && data.cmd[0] != '\n')
		{
			data.cmd = ft_trim(data.cmd);
			add_history(data.cmd);
			ft_lexer(&data);
			free(data.cmd);
			data.error = ft_syntax_analyzer(&data);
			if (data.error)
			{
				ft_free_lexer(data.lst_lexer);
				continue;
			}
			data.error = ft_syntax_analyzer(&data);
			if (data.error)
				continue;
			ft_expanding(&data);
			ft_print_lexer(data.lst_lexer);
			ft_parsing(&data);
			ft_print_lexer(data.lst_lexer);
			ft_delete_quotes(&data);
			ft_print_cmd(data.lst_cmd);
			// if (data.lst_cmd)
				// echo(&data, data.lst_cmd, data.lst_cmd->fd_in);
			// cd(&data, data.lst_cmd);
			// pwd(&data, data.lst_cmd, 1);
			// ft_print_lexer(data.lst_lexer);
			// comment this if you want to edit the parsing to avoid segfaults
			// also you can run single cmnts right now
			// unset(&data, "zzz");
			// printf("%d\n", export(&data, data.lst_cmd, 1));
			// exe(&data);
			ft_free_lexer(data.lst_lexer);
			// ft_free_cmd(data.lst_cmd);
		}
	}
	return (0);
}

// /Users/yabtaour/Desktop/Minishell