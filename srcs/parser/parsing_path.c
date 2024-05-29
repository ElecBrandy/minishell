/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:27:48 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/29 13:38:00 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	find_path_two(char *cmd, t_env *e, t_node *node);
static int	get_path(char **path, t_node *node, char *cmd);
static int	check_path(char **path, t_node *node, char *cmd, int *i);

static int	check_path(char **path, t_node *node, char *cmd, int *i)
{
	if (cmd[0] == '.' || cmd[0] == '/')
	{
		if (access(cmd, X_OK) == 0)
		{
			node->path = ft_strdup(cmd);
			if (!(node->path))
				return (12);
			return (0);
		}
	}
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
	node->path = NULL;
	return (1);
}

int	check_file_or_cmd(char *cmd, char *tmp)
{
	if (tmp)
		free(tmp);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
		{
			printf("minishell: %s: is a directory\n", cmd);
			g_signal_error = 126;
		}
		else
		{
			printf("minishell: %s: No such file or directory\n", cmd);
			g_signal_error = 127;
		}
	}
	else
	{
		printf("minishell: %s: command not found\n", cmd);
		g_signal_error = 127;
	}
	return (g_signal_error);
}

static int	get_path(char **path, t_node *node, char *cmd)
{
	t_util	u;
	char	*temp;
	char	*tmp;

	util_init(&u);
	temp = ft_strdup(cmd);
	tmp = ft_strtrim(temp, "./");
	if (is_builtin(node) == 0)
	{
		if (!tmp[0] && cmd[0] != 0)
			return (check_file_or_cmd(cmd, tmp));
		free(tmp);
		u.flag = check_path(path, node, cmd, &u.i);
		if (u.flag == 0 || u.flag == 12)
			return (u.flag);
		if (!path[u.i])
			return (check_file_or_cmd(cmd, NULL));
	}
	else
	{
		free(tmp);
		node->path = ft_strdup(cmd);
	}
	return (0);
}

static int	find_path_two(char *cmd, t_env *e, t_node *node)
{
	char	**path;
	char	*env_path;

	if (cmd[0] == 0)
		return (check_file_or_cmd(cmd, NULL));
	env_path = ft_strdup(e->value);
	if (!env_path)
		return (1);
	path = ft_split(env_path, ':');
	free(env_path);
	if (!path)
		return (1);
	if (ft_strchr(cmd, '/') && cmd[0] == '/' && is_path(cmd) == 1)
	{
		check_file_or_cmd(cmd, NULL);
		free_str(path);
		return (1);
	}
	g_signal_error = get_path(path, node, cmd);
	free_str(path);
	if (g_signal_error || !(node->path))
		return (1);
	return (0);
}

int	find_path(char *cmd, t_env *env, t_node *node)
{
	t_env	*e;

	if (!cmd)
		return (0);
	e = env;
	while (e)
	{
		if (ft_strncmp(e->key, "PATH", 4) == 0)
			break ;
		e = e->next;
	}
	if (!e)
	{
		if (is_builtin(node))
			return (0);
		if (is_path(cmd))
			return (check_file_or_cmd(cmd, NULL));
		node->path = ft_strdup(cmd);
		return (0);
	}
	if (find_path_two(cmd, e, node) || g_signal_error)
		return (file_error());
	return (g_signal_error);
}
