#include "../minishell.h"

int	ft_is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	result;
	unsigned char *new;

	new = (unsigned char *) str;
	sign = 1;
	result = 0;
	i = 0;
	while (new[i] == '\t' || new[i] == '\n'
		|| new[i] == '\r' || new[i] == '\v'
		|| new[i] == ' ' || new[i] == '\f')
		i++;
	if (new[i] == '+')
		i++;
	else if (new[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (new[i] >= '0' && new[i] <= '9')
	{
		result = (result * 10) + (new[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_exit(t_data *data, t_cmd *lst_cmd, int fd)
{
	if (lst_cmd->cmd[0] && lst_cmd->cmd[1] && !lst_cmd->cmd[2])
	{
		if (!lst_cmd->next)
			ft_putstr_fd("exit\n", fd);
		if (!ft_is_num(lst_cmd->cmd[1]))
		{
			ft_putstr_fd("numeric argument required\n", fd);
			return (255);
		}
		else
			return (ft_atoi(lst_cmd->cmd[1]));
	}
	if (lst_cmd->cmd[0] && lst_cmd->cmd[1] && lst_cmd->cmd[2])
	{
		if (!lst_cmd->next)
			ft_putstr_fd("exit\n", fd);
		ft_putstr_fd("too many arguments\n", fd);
		return (1);
	}
	if (lst_cmd->cmd[0] && !lst_cmd->cmd[1])
	{
		if (!lst_cmd->next)
			ft_putstr_fd("exit\n", fd);
		return (0);
	}
	return (0);
}