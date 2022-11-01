/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssabbaji <ssabbaji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 18:17:17 by yabtaour          #+#    #+#             */
/*   Updated: 2022/09/19 16:29:22 by ssabbaji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_delete_node_red(t_data *data, int position)
{
	t_lexer	*lexer_clone;
	t_lexer	*lexer_clone2;
	int		i;

	i = -1;
	lexer_clone = data->lst_lexer;
	while (lexer_clone && ++i < position)
		lexer_clone = lexer_clone->next;
	if (lexer_clone)
	{
		if (lexer_clone && lexer_clone->next)
			lexer_clone->next->prev = lexer_clone->prev;
		if (lexer_clone && lexer_clone->prev)
			lexer_clone->prev->next = lexer_clone->next;
		lexer_clone2 = lexer_clone->next;
		free(lexer_clone->val);
		free(lexer_clone);
		lexer_clone = lexer_clone2;
	}
	if (!i)
		data->lst_lexer = lexer_clone;
}

void	ft_delete_red_norme(t_data *data, int position, int flag)
{
	t_lexer	*lexer_clone;

	lexer_clone = data->lst_lexer;
	while (lexer_clone && lexer_clone->type != PIPE)
	{
		flag = 0;
		if (lexer_clone && lexer_clone->type == REDIRECTION
			&& ft_strcmp(lexer_clone->val, "<<"))
		{
			flag = 1;
			position++;
			lexer_clone = lexer_clone->next;
			while (lexer_clone && lexer_clone->type != REDIRECTION)
			{
				ft_delete_node_red(data, position);
				position--;
				lexer_clone = lexer_clone->prev;
			}
			ft_delete_node_red(data, position);
		}
		if (!flag)
			position++;
		if (lexer_clone)
			lexer_clone = lexer_clone->next;
	}
}

void	ft_delete_redirections(t_data *data)
{
	t_lexer	*lexer_clone;
	int		position;

	while (ft_check_still_redirection(data))
	{
		ft_delete_red_norme(data, 0, 0);
		lexer_clone = data->lst_lexer;
		position = 0;
		while (lexer_clone && lexer_clone->type != PIPE)
		{
			if (lexer_clone && lexer_clone->type == REDIRECTION
				&& ft_strcmp(lexer_clone->val, "<<"))
				ft_delete_node_red(data, position);
			position++;
			lexer_clone = lexer_clone->next;
		}
		lexer_clone = data->lst_lexer;
	}
}

char	*ft_new(char *old)
{
	char	*new;
	int		len;

	len = ft_strlen(old);
	new = NULL;
	if (ft_exist_quotes(old))
	{
		new = ft_delete(old);
		return (new);
	}
	else
	{
		new = ft_substr(old, 0, len);
		return (new);
	}
}
