/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 19:04:35 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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

static int	cd_withoutarg(t_env **env);
static int	cd_witharg(t_env **env, t_node *node, char *path);
static int	check_path(char *path);
static int	move_path(t_env **env, char *path);

void	ft_cd(t_env **env, t_node *node)
{
	int	error;

	if (ft_arrlen_2d(node->cmd) == 1)
	{
		error = cd_withoutarg(env);
		ft_cd_error1(error, node->cmd[1]);
	}
	else
	{
		error = cd_witharg(env, node, node->cmd[1]);
		ft_cd_error1(error, node->cmd[1]);
	}
}

static int	cd_withoutarg(t_env **env)
{
	t_env	*cur;

	cur = is_env(*env, "HOME");
	if (!cur)
		return (1);
	else
	{
		if (ft_strncmp(cur->cmd, "HOME", ft_strlen(cur->cmd)) == 0)
			return (1);
		else if (ft_strncmp(cur->cmd, "HOME=", ft_strlen(cur->cmd)) == 0)
		{
			return (move_path(env, "."));
		}
		else
		{
			return (move_path(env, cur->value));
		}
	}
	return (0);
}

static int	cd_witharg(t_env **env, t_node *node, char *path)
{
	int		error;

	if ((ft_strlen(path) == 1 && path[0] == '~') \
	|| (ft_strlen(path) == 1 && path[0] == '-'))
		error = 2;
	else
		error = check_path(node->cmd[1]);
	if (error != 0)
		return (error);
	return (move_path(env, node->cmd[1]));
}

static int	check_path(char *path)
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

static int	move_path(t_env **env, char *path)
{
	int		error;
	char	pwd[PATH_MAX];
	char	oldpwd[PATH_MAX];

	if (!env)
		return (1);
	error = 0;
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		ft_cd_error2(1);
	else
		error = update_oldpwd(env, oldpwd);
	if (chdir(path) == -1)
		ft_cd_error2(3);
	if (getcwd(pwd, PATH_MAX) == NULL)
		ft_cd_error2(2);
	else
		error = update_pwd(env, pwd);
	
	return (error);
}
