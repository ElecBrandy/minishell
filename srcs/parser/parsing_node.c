/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:12:40 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/16 19:12:53 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_in_node(t_node *node, char **cmd, t_env e)
{
	int	i;

	i = count_str(cmd);
	node->cmd = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (cmd[++i])
		node->cmd[i] = ft_strdup(cmd[i]);
	node->cmd[i] = NULL;
	find_path(cmd[0], e.arr, node);
}

void	find_path(char *cmd, char **env, t_node *node)
{
	char	*env_path;
	char	**path;
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
	}
	env_path = ft_strdup(env[i] + 5);
	path = ft_split(env_path, ':');
	free(env_path);
	if (access(cmd, X_OK) == 0)
	{
		node->path = ft_strdup(cmd);
		return ;
	}
	get_path(path, node, cmd);
	free_str(path);
}

void	get_path(char **path, t_node *node, char *cmd)
{
	int	i;

	i = -1;
	while (path[++i])
	{
		node->path = ft_strjoin(path[i], "/");
		node->path = ft_strjoin_free(node->path, cmd);
		if (access(node->path, X_OK) == 0)
			return ;
		else
			free(node->path);
	}
	if (!path[i])
		exit (2);//빌트인함수 따로 처리
}

t_node	*create_node(void)
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
