/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:33 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/26 13:26:59 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// herdoc can output to the cmd like wc
// in bash herdoc do not output to a file just created
// the herdoc before the syntax error

int	her_finished(t_data *data, t_cmd *cmd_clone, int **pip, int i)
{
	close(cmd_clone->fd_in);
	close(cmd_clone->her_in);
	close_fds(cmd_clone);
	close_pipes(pip, data->general.lent);
	exit(0);
}

void	print_for_her(t_cmd *cmd_clone, char *buff)
{
	ft_putstr_fd(buff, cmd_clone->her_in);
	ft_putstr_fd("\n", cmd_clone->her_in);
}

int	ft_herdoc(t_data *data, t_cmd *cmd_lst, int **pip, int i)
{
	int		pid;
	char	*buff;
	t_cmd	*cmd_clone;
	int		idx = 0;

	cmd_clone = cmd_lst;
	where_ami = 0;
	pid = fork();
	if (cmd_clone->her_doc_num && pid == 0)
	{
		while (1 && idx < cmd_lst->her_doc_num)
		{
			buff = readline("heredoc> ");
			if (!buff)
				exit (1);
			else if (buff[0] != '\0' && !ft_strcmp(buff, data->eof[i]))
			{
				i++;
				idx++;
			}
			else
				print_for_her(cmd_clone, buff);
		}
		her_finished(data, cmd_clone, pip, i);
	}
	waitpid(pid, 0, 0);
	kill(pid, SIGKILL);
	return (1);
}
