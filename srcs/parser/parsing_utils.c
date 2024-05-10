/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:26:19 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/08 10:28:50 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_in_node(t_node *node, char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	node->cmd = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (cmd[++i])
		node->cmd[i] = ft_strdup(cmd[i]);
	node->cmd[i] = NULL;
}

void	util_init(t_util *util)
{
	util->i = -1;
	util->start = 0;
	util->end = 0;
	util->idx = -1;
	util->flag = 0;
	util->j = -1;
}

t_node	*make_node(t_node *head)
{
	t_node	*str;
	t_node	*node;

	str = malloc(sizeof(t_node));
	str->next = NULL;
	str->cmd = NULL;
	str->path = NULL;
	str->in_fd = 0;
	str->out_fd = 1;
	if (head)
	{
		node = head;
		while (node->next)
			node = node->next;
		node->next = str;
	}
	else
		node = str;
	return (str);
}

int	find_next_quote(char *av, int idx, char flag)
{
	while (av[++idx])
	{
		if (av[idx] == flag)
			return (idx);
	}
	// 따옴표가 안닫혀있으면 에러처리
	exit (1);
}

int	find_flag(char *av, char flag)
{
	int	idx;
	int	len;

	len = 0;
	idx = -1;
	while (av[++idx])
	{
		if (av[idx] == flag)
			len++;
		else if (av[idx] == 34)
			idx = find_next_quote(av, idx, 34);
		else if (av[idx] == 39)
			idx = find_next_quote(av, idx, 39);
	}
	return (len);
}
