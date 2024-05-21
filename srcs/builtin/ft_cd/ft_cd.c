/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 20:45:23 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_cd
	cd with only a relative or absolute path

	파싱부분에서 환경변수를 받아오지 못할 경우에 대하여..? 에러처리? 어떤 식으로 넘어오는지?
	unset HOME 한 후 cd $HOME 했을 때
	인자가 n개일때의 오류 -> 메세지상에서 무조건 첫번째 인자
*/

void ft_cd(t_env *head_env, t_node *node)
{
	int	i;
	char	*pwd;
	char	*oldpwd;

	if (ft_arrlen_2d(node->cmd) == 1) // 인자가 없는 경우 HOME 경로로 이동
		move_home();
	else // 인자가 있는 경우
	{
		if () // cd ~ (이후 어떤 인자가 오던지 HOME 경로로 이동)
			move_home();
		else if () // cd - (이전 경로로 이동)
			move_previous();
		else // cd [path] (해당 경로로 이동)
			move_path();
	}
}

void	move_path(char *path, char *pwd, char *oldpwd)
{

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		ft_putstr_fd("error?\n", 2); // Error?
		return ;
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_errnum = 1;
	}
	else
	{
		pwd = getcwd(NULL, 0);
		change_env("OLDPWD", oldpwd);
		change_env("PWD", pwd);
		ft_free((void **)&pwd);
	}
	ft_free((void **)&oldpwd);
}