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

	unlink(".heredoc_tmp");
	while (head)
	{
		node = head->next;
		if (head->in_fd != 0)
			close(head->in_fd);
		if (head->out_fd != 1)
			close(head->out_fd);
		if (head->cmd)
			free_str(head->cmd);
		if (head->path != NULL)
			free(head->path);
		free(head);
		head = node;
	}
	head = NULL;
}

void	free_str_three(char ***str)
{
	int	i;

	i = -1;
	while (str[++i])
		free_str(str[i]);
	ft_free((void **)&str);
	str = NULL;
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

int	count_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**free_all(char **cmd, char **str)
{
	free(cmd);
	free_str(str);
	return (NULL);
}
