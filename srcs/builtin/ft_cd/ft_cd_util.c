/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:55:25 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/22 22:16:21 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	move_path(t_env *head_env, const char *path)
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

static int update_pwd(t_env *head_env, char *cur_path)
{
	t_env	*cur;
	char	*new_cmd;

	cur = is_env(head_env, "PWD");
	if (!cur) // key 가 없는 경우
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
			return (FALSE);
		add_env(head_env, new_cmd, "PWD", cur_path);
	}
	else // key 가 있는 경우
	{
		new_cmd = ft_strjoin(tmp, cur_path);
		if (!new_cmd)
		{
			ft_free((void **)&tmp);
			return (FALSE);
		}
		renew_env(cur, "PWD", "PWD", cur_path);
	}
	return (TRUE);	
}
