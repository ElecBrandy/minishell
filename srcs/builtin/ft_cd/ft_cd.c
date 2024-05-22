/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/23 03:51:25 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		cd_withoutarg(t_env *head_env, t_node *node);
static void		cd_witharg(t_env *head_env, t_node *node);
static int		check_path(char *path);
static int		move_path(t_env *head_env, char *path);

void ft_cd(t_env *head_env, t_node *node)
{
	if (ft_arrlen_2d(node->cmd) == 1) // 인자가 없는 경우 HOME 경로로 이동
	{
		cd_withoutarg(head_env, node);
	}
	else // 인자가 있는 경우
	{
		cd_witharg(head_env, node);
	}
}

static void	cd_withoutarg(t_env *head_env, t_node *node)
{
	t_env *env;

	env = is_env(head_env, "HOME");
	if (!env) // 환경변수에 '$HOME'이 없는 경우
	{
		ft_cd_error(5, "HOME"); // Error // Error bash: cd: HOME not set
		return ;
	}
	else // 환경변수에 '$HOME'이 있는 경우
	{
		if (ft_strncmp(env->cmd, "HOME", ft_strlen(env->cmd)) == 0) // 'HOME' 인경우
		{
			ft_cd_error(5, "HOME"); // Error bash: cd: HOME not set
		}
		else if (ft_strncmp(env->cmd, "HOME=", ft_strlen(env->cmd)) == 0) // 'HOME=' 인경우
		{
			move_path(head_env, ".");
		}
		else
		{
			move_path(head_env, env->value);
		}
	}
	return ;
}

static void	cd_witharg(t_env *head_env, t_node *node)
{
	int		check;

	check = check_path(node->cmd[1]);
	if (check != 0)
	{
		ft_cd_error(check, node->cmd[1]); // Error
	}
	else
	{
		move_path(head_env, node->cmd[1]);
	}
	return ;
}

static int check_path(char *path)
{
	int	fd;

	if (access(path, F_OK) == -1) // 경로가 존재하는가?
	{
		return (1); // 경로가 존재하지 않음 : bash: cd: path: No such file or directory
	}
	if (access(path, X_OK) == -1) // 접근 권한이 있는가?
	{
		return (2); // 접근 권한이 없음 : bash: cd: path: Permission denied
	}
	fd = open(path, O_DIRECTORY); // 경로가 폴더가 맞는가? (파일일수도 있으니까)
	if (fd == -1)
		return (3); // Error : bash: cd: path: Not a directory
	close(fd);
	return (0);
}

static int	move_path(t_env *head_env, char *path)
{
	int		signal;
	char	*cur_path;
	char	*pre_path;

	signal = FALSE;
	pre_path = getcwd(NULL, 0);
	if (!pre_path)
		return (signal); // Error
	if (chdir(path) == -1)
		return (signal); // Error
	cur_path = getcwd(NULL, 0);
	if (!cur_path)
	{
		ft_free((void **)&pre_path);
		return (signal); // Error
	}
	if (update_pwd(head_env, cur_path))
		signal = TRUE;
	if (update_oldpwd(head_env, pre_path)) // 디렉토리 변경 성공 시 $OLDPWD 갱신
		signal = TRUE;
	ft_free((void **)&pre_path);
	ft_free((void **)&cur_path);
	ft_free((void **)&pre_path);
	return (signal);
}
