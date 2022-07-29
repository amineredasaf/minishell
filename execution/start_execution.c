/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsaf <rsaf@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 12:22:38 by rsaf              #+#    #+#             */
/*   Updated: 2022/07/29 13:49:09 by rsaf             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_wait_nd_kill(int idx)
{
	int	pid;
	int	status;

	while (idx > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status) == 0)
			return (130);
		if (WIFEXITED(status) && WEXITSTATUS(status) != -1 && pid != -1)
			kill(pid, SIGKILL);
		idx--;
	}
	return (WEXITSTATUS(status));
}

void	ft_finished_exe(t_data *data, int **pip, int idx)
{
	close_pipes(pip, data->general.lent);
	close_fds(data->lst_cmd);
	if (idx)
		data->error = ft_wait_nd_kill(idx);
}

int	ft_fork(t_data *data, int idx)
{
	if (data->general.pid != 0 && data->error == -666)
	{
		idx++;
		g_where_ami = 0;
		data->general.pid = fork();
	}
	return (idx);
}

int	start_execution(t_data *data, int **pip, int idx)
{
	t_cmd	*cmd_clone;
	char	*cmd_path;

	cmd_clone = data->lst_cmd;
	cmd_path = NULL;
	while (cmd_clone)
	{
		data->error = non_fork_funcs(data, cmd_clone, pip);
		idx = ft_fork(data, idx);
		if (data->general.pid == 0 && cmd_clone->fd_in != -69)
		{
			ft_dup(data->general.lent, cmd_clone, pip);
			close_fds(cmd_clone);
			close_pipes(pip, data->general.lent);
			data->error = ft_if_builtin(data, cmd_clone);
			if (data->error == 2)
				cmd_path = ft_cmd_exist(data, cmd_clone, -1);
			if (cmd_path)
				ft_execute_cmd(data, cmd_path, cmd_clone);
			exit(1);
		}
		cmd_clone = cmd_clone->next;
	}
	ft_finished_exe(data, pip, idx);
	return (0);
}
