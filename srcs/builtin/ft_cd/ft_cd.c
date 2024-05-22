/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/22 21:55:09 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		cd_withoutarg(t_env *head_env, t_node *node);
static void		cd_witharg(t_env *head_env, t_node *node);
static int		check_path(char *path);
static t_env	*is_env(t_env *head_env, char *key);
static void		move_path(const char *path);
/*
	ft_cd
	cd with only a relative or absolute path

	인자가 여러개 들어와도 첫번째 인자만 처리
	파싱부분에서 환경변수를 받아오지 못할 경우에 대하여..? 에러처리? 어떤 식으로 넘어오는지?
	unset HOME 한 후 cd $HOME 했을 때
	인자가 n개일때의 오류 -> 메세지상에서 무조건 첫번째 인자

	unset HOME 한 후 cd $HOME 했을 때 
	-> bash: cd: HOME not set

	unset PWD 한 후 cd $PWD 했을 때 //파싱?
	-> bash: cd: PWD not set

	케이스분류
	1. 'HOME'
	- cd $HOME : bash: cd: HOME not set // Error  ::: cd
	- cd : bash: cd: HOME not set ::: cd
	- cd ~ : 정상동작 ::: cd ~

	2. 'HOME='
	- cd $HOME : cd . 처럼 동작 ::: cd
	- cd : cd . 처럼 동작 ::: cd
	- cd ~ : 정상동작 ::: cd ~

	구분1 cd_withnoarg
	- cd $HOME : bash: cd: HOME not set // Error  ::: cd
	- cd : bash: cd: HOME not set ::: cd
	- cd $HOME : cd . 처럼 동작 ::: cd ("$HOME=")
	- cd : cd . 처럼 동작 ::: cd

	구분2 cd_witharg
*/

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
	if (!env) // 'HOME'이 없는 경우
	{
		ft_cd_error(); // Error bash: cd: HOME not set
		return ;
	}
	else // 'HOME'이 있는 경우
	{
		if (ft_strncmp(env->cmd, "HOME", ft_strlen(env->cmd)) == 0) // 'HOME' 인경우
		{
			ft_cd_error(); // Error bash: cd: HOME not set
		}
		else if (ft_strncmp(env->cmd, "HOME=", ft_strlen(env->cmd)) == 0) // 'HOME=' 인경우
		{
			move_path(".");
		}
		else // 정상동작
		{
			move_path(env->value);
		}
	}
	return ;
}

void	cd_witharg(t_env *head_env, t_node *node)
{
	int		check;

	check = check_path(node->cmd[1]);
	if (check != 0)
	{
		ft_cd_error(); // Error
	}
	else
	{
		move_path(node->cmd[1]);
	}
	return ;
}

static int check_path(char *path)
{
	int	fd;

	if (access(path, F_OK) == -1) // 경로가 존재하는가?
	{
		return (2); // 경로가 존재하지 않음 : bash: cd: path: No such file or directory
	}
	if (access(path, X_OK) == -1) // 접근 권한이 있는가?
	{
		return (3); // 접근 권한이 없음 : bash: cd: path: Permission denied
	}
	fd = open(path, O_DIRECTORY); // 경로가 폴더가 맞는가? (파일일수도 있으니까)
	if (fd == -1)
		return (3); // Error : bash: cd: path: Not a directory
	close(fd);
	return (0);
}

static t_env *is_env(t_env *head_env, char *key)
{
	t_env	*cur;

	cur = head_env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0)
		{
			return (cur);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	move_path(const char *path)
{
	char	*cur_path;
	char	*pre_path;

	pre_path = getcwd(NULL, 0);
	if (!pre_path)
	{
		return ; // Error
	}
    if (chdir(path) == -1)
	{
        ft_cd_err();  // 디렉토리 변경 실패 시 에러 출력
        return; // Error
    }
	cur_path = getcwd(NULL, 0);
	if (!pre_path)
	{
		ft_free((void **)&pre_path);
		return ;
	}
    update_pwd(head_env, cur_path); // 디렉토리 변경 성공 시 $PWD 갱신
	update_oldpwd(head_env, pre_path); // 디렉토리 변경 성공 시 $OLDPWD 갱신
    ft_free((void **)&cur_path);
	ft_free((void **)&pre_path);
}
