/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 16:12:27 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_cd
	- Change directory

	error_log
	0 : Success
	1 : minishell: cd: HOME not set
	2 : minishell: cd: path: No such file or directory
	3 : minishell: cd: path: Permission denied
	4 : minishell: cd: path: Not a directory
	12 : malloc error;
	ex : perror
*/

static int	cd_withoutarg(t_env *head_env, t_node *node);
static int	cd_witharg(t_env *head_env, t_node *node, char *path, char *home);
static int	check_path(char *path);
static int	move_path(t_env *head_env, char *path);

void ft_cd(t_env *head_env, t_node *node, char *home)
{
	int		error;

	if (ft_arrlen_2d(node->cmd) == 1)
	{
		error = cd_withoutarg(head_env, node);
		ft_cd_error(error, node->cmd[1]);
	}
	else
	{
		error = cd_witharg(head_env, node, node->cmd[1], home);
		ft_cd_error(error, node->cmd[1]);
	}
}

static int	cd_withoutarg(t_env *head_env, t_node *node)
{
	t_env	*env;

	env = is_env(head_env, "HOME");
	if (!env)
		return (1);
	else
	{
		if (ft_strncmp(env->cmd, "HOME", ft_strlen(env->cmd)) == 0)
			return (1);
		else if (ft_strncmp(env->cmd, "HOME=", ft_strlen(env->cmd)) == 0)
		{
			return (move_path(head_env, "."));
		}
		else
		{
			return (move_path(head_env, env->value));
		}
	}
	return (0);
}

static int	cd_witharg(t_env *head_env, t_node *node, char *path, char *home)
{
	
	int		error;

	if (ft_strlen(path) == 1 && path[0] == '~')
		return (move_path(head_env, home));
	else if (ft_strlen(path) == 1 && path[0] == '-')
		return (move_path(head_env, is_env(head_env, "OLDPWD")->value));
	error = check_path(node->cmd[1]);
	if (error != 0)
		return (error);
	return (move_path(head_env, node->cmd[1]));
}

static int check_path(char *path)
{
	int	fd;

	if (access(path, F_OK) == -1)
		return (2);
	if (access(path, X_OK) == -1)
		return (3);
	fd = open(path, O_DIRECTORY);
	if (fd == -1)
		return (4);
	close(fd);
	return (0);
}

static int	move_path(t_env *head_env, char *path)
{
	char	*cur_path;
	char	*pre_path;

	if (!head_env)
		return (1);
	pre_path = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (12);
	if (!pre_path)
		return (12);
	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		ft_free((void **)&pre_path);
		return (12);
	}
	if (update_pwd(head_env, cur_path) == FALSE)
		return (12);
	if (update_oldpwd(head_env, pre_path) == FALSE)
		return (12);
	ft_free((void **)&pre_path);
	ft_free((void **)&cur_path);
	return (0);
}
