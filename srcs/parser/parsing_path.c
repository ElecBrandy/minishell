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

int	check_path(char **path, t_node *node, char *cmd, int *i)
{
	while (path[++(*i)])
	{
		node->path = ft_strjoin(path[*i], "/");
		node->path = ft_strjoin_free(node->path, cmd);
		if (!(node->path))
			return (12);
		if (access(node->path, X_OK) == 0)
			return (0);
		else
			free(node->path);
	}
	return (1);
}

int	get_path(char **path, t_node *node, char *cmd)
{
	int	i;
	int	flag;

	i = -1;
	if (is_builtin(node) == 0)
	{
		flag = check_path(path, node, cmd, &i);
		if (flag == 0 || flag == 12)
			return (flag);
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

int	find_path_two(char *cmd, t_env *env, t_node *node, char **path)
{
	if (access(cmd, X_OK) == 0)
		node->path = ft_strdup(cmd);
	else
		g_signal_error = get_path(path, node, cmd);
	free_str(path);
	if (g_signal_error)
		return (g_signal_error);
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
	i = find_path_two(cmd, env, node, path);
	if (i)
		return (i);
	return (g_signal_error);
}
