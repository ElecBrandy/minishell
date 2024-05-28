/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/28 19:44:25 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	run_cmd(t_env *head_env, t_node *node);
static char	*check_path(char **envp, char *cmd);
static char	*make_path(char **path_list, char *cmd);
static int is_onlycmd(char *cmd);

int	ft_execve(t_env *head_env, t_node *node, char *home, pid_t pid)
{
	int	error;

	if (is_builtin(node) != 0)
		exec_builtin(head_env, node, home, pid);
	else
	{
		error = run_cmd(head_env, node);
		if (error == 88)
			g_signal_error = 12;
		print_error();
	}
	exit(g_signal_error);
}

static int run_cmd(t_env *head_env, t_node *node)
{
	char	*path;
	char	**envp;

	envp = env_list_to_array(head_env);
	if (!envp)
		return (88);
	path = check_path(envp, node->cmd[0]);
	if (!path)
		return (88);
	if (execve(path, node->cmd, envp) == -1)
		return (127);
	return (0);
}

static char *check_path(char **envp, char *cmd)
{
	char	*path;
	char	**path_list;

	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	path_list = ft_split(*envp + 5, ':');
	if (!path_list)
		return (NULL);
	path = make_path(path_list, cmd);
	if (!path)
		return (NULL);
	return (path);
}

static char *make_path(char **path_list, char *cmd)
{
	char	*tmp;
	char	*path;

	if (is_onlycmd(cmd) == TRUE)
	{
		while (*path_list)
		{
			tmp = ft_strjoin(*path_list, "/");
			if (!tmp)
				return (NULL);
			path = ft_strjoin(tmp, cmd);
			ft_free((void **)&tmp);
			if (!path)
				return (NULL);
			if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
				return (path);
			ft_free((void **)&path);
			path_list++;
		}
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

static int is_onlycmd(char *cmd)
{
	if (cmd == NULL)
		return (TRUE);
	if (cmd[0] == '/')
		return (FALSE);
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (FALSE);
	return (TRUE);
}
