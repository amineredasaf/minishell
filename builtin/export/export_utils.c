/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabtaour <yabtaour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 17:56:21 by yabtaour          #+#    #+#             */
/*   Updated: 2022/07/27 17:56:22 by yabtaour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_change_env_value(t_data *data, char *name, char *value, int size)
{
	t_env	*env_clone;

	env_clone = data->lst_env;
	while (env_clone)
	{
		if (ft_strcmp(name, env_clone->name) == 0)
		{
			free(env_clone->value);
			if (!value || !ft_strlen(value))
			{
				env_clone->value = malloc (1);
				env_clone->value[0] = '\0';
			}
			else
				env_clone->value = ft_substr(value, 0, ft_strlen(value));
		}
		env_clone = env_clone->next;
	}
	return (0);
}

int	ft_name_exists(t_data *data, char *name)
{
	t_env	*env_clone;

	if (!name)
		return (0);
	env_clone = data->lst_env;
	while (env_clone)
	{
		if (ft_strcmp(name, env_clone->name) == 0)
			return (1);
		env_clone = env_clone->next;
	}
	return (0);
}

char	*ft_get_name_exp(char *name)
{
	int		i;
	char	*new_name;

	new_name = NULL;
	i = 0;
	if (!name)
		return (NULL);
	while (name[i] && name[i] != '=')
		i++;
	new_name = ft_substr(name, 0, i);
	return (new_name);
}

char	*ft_get_value_exp(char *value)
{
	int		i;
	int		j;
	int		origin;
	char	*new_value;

	i = 0;
	j = 0;
	new_value = NULL;
	if (!value)
		return (NULL);
	while (value[i] && value[i] != '=')
		i++;
	if (value[i])
	{
		origin = i + 1;
		while (value[++i])
			j++;
		new_value = ft_substr(value, origin, j);
	}
	return (new_value);
}
