/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:27:48 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/21 19:29:27 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_path(char **path, t_node *node, char *cmd)
{
	int	i;

	i = -1;
	if (is_builtin(node) == 0)
	{
		while (path[++i])
		{
			node->path = ft_strjoin(path[i], "/");
			node->path = ft_strjoin_free(node->path, cmd);
			if (!(node->path))
				return (12);
			if (access(node->path, X_OK) == 0)
				return (0);
			else
				free(node->path);
		}
		if (!path[i])
		{
			node->path = NULL;
			printf("minishell: %s: command not found\n", cmd);
			return (127);
		}
	}
	else
		node->path = ft_strdup(cmd);
	if (!(node->path))
		return (12);
	return (0);
}

int	find_path(char *cmd, t_env *env, t_node *node)
{
	char	*env_path;
	char	**path;
	int		i;
	t_env	*e;

	if (!cmd)
		return (1);
	e = env;
	while (e->cmd)
	{
		if (ft_strncmp(e->key, "PATH", 4) == 0)
			break ;
		e = e->next;
	}
	env_path = ft_strdup(e->value);
	if (!env_path)
		return (12);
	path = ft_split(env_path, ':');
	free(env_path);
	if (!path)
		return (12);
	if (access(cmd, X_OK) == 0)
		node->path = ft_strdup(cmd);
	else
		g_errnum = get_path(path, node, cmd);
	free_str(path);
	if (g_errnum)
		return (g_errnum);
	if (!(node->path))
		return (12);
	return (g_errnum);
}
