/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:10:20 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/12 02:43:30 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node *head)
{
	t_node	*node;

	while (head)
	{
		node = head->next;
		free_str(head->cmd);
		ft_free((void **)&head->path);
		ft_free((void **)&head);
		head = node;
	}
}

void	free_str_three(char ***str)
{
	int	i;

	i = -1;
	while (str[++i])
		free_str(str[i]);
	ft_free((void **)&str);
}

void	free_str(char **str)
{
	int	i;

	i = -1;
	if (!str)
		return ;
	while (str[++i])
	{
		ft_free((void **)&str[i]);
		str[i] = NULL;
	}
	ft_free((void **)&str);
}
