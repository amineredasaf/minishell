/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_and.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:16:33 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/26 18:16:34 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_add_and(t_data *data, int i)
{
	int		origin;
	int		len;
	char	*command;

	origin = i;
	len = 0;
	command = NULL;
	while (data->cmd[i] && data->cmd[i] == '&')
	{
		i++;
		len++;
	}
	command = ft_substr(data->cmd, origin, len);
	data->lst_lexer = ft_add_lexer_back(data->lst_lexer, command, AND);
	free(command);
	return (i);
}
