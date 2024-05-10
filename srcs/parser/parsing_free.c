/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:10:20 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/10 09:10:22 by dongeunk         ###   ########.fr       */
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
		free(head->path);
		free(head);
		head = node;
	}
}

void	free_str_three(char ***str)
{
	int	i;

	i = -1;
	while (str[++i])
		free_str(str[i]);
	free(str);
}

void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}
