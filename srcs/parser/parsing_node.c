/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:28:12 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/29 13:36:38 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_path(char *cmd)
{
	if (!ft_strncmp(cmd, "/usr/local/bin", 14)
		|| !ft_strncmp(cmd, "/usr/bin", 8)
		|| !ft_strncmp(cmd, "/bin", 4) || !ft_strncmp(cmd, "/usr/sbin", 9)
		|| !ft_strncmp(cmd, "/sbin", 5)
		|| !ft_strncmp(cmd, "/usr/local/munki", 16)
		|| !ft_strncmp(cmd, "/Library/Apple/usr/bin", 22))
		return (0);
	return (1);
}

int	save_in_node(t_node *node, char **cmd)
{
	int	i;

	i = count_str(cmd);
	node->cmd = malloc(sizeof(char *) * (i + 1));
	if (!node->cmd)
	{
		free_str(cmd);
		return (12);
	}
	i = -1;
	while (cmd[++i])
	{
		node->cmd[i] = ft_strdup(cmd[i]);
		if (!node->cmd[i])
		{
			free_str(cmd);
			return (12);
		}
	}
	node->cmd[i] = NULL;
	free_str(cmd);
	return (g_signal_error);
}

t_node	*create_node(int p_e)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->next = NULL;
	node->cmd = NULL;
	node->path = NULL;
	node->in_fd = 0;
	node->out_fd = 1;
	node->prev_errnum = p_e;
	return (node);
}

void	append_node(t_node **head, t_node *new_node)
{
	t_node	*cur;

	cur = *head;
	if (!cur)
		(*head) = new_node;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}

void	util_init(t_util *util)
{
	util->i = -1;
	util->start = 0;
	util->end = 0;
	util->idx = -1;
	util->flag = 0;
	util->j = -1;
	util->cnt = 0;
	util->prev_errnum = g_signal_error;
}
