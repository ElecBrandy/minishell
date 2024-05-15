/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:56:28 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/15 18:57:42 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
echo with option -n : 7
-n 옵션을 사용할 수 있는 echo

cd with only a relative or absolute path : 6
오직 상대 또는 절대경로만 사용하는 cd

pwd with no options : 5

export with no options : 4

unset with no options : 3

env with no options or arguments : 2

exit with no options : 1

builtin 함수가 아닐 경우 : 0
*/


int		is_builtin(t_node *node)
{
	if (ft_strncmp(node->cmd[0], "echo", ft_strlen("echo")) == 0) // 내부에서 -n 옵션 체크 하기
		return (7);
	if (ft_strncmp(node->cmd[0], "cd", ft_strlen("env")) == 0) // 내부에서 경로체크 따로 하기
		return (6);
	if (ft_strncmp(node->cmd[0], "pwd", ft_strlen("pwd")) == 0)
		return (5);
	if (ft_strncmp(node->cmd[0], "export", ft_strlen("export")) == 0)
		return (4);
	if (ft_strncmp(node->cmd[0], "unset", ft_strlen("export")) == 0)
		return (3);
	if (ft_strncmp(node->cmd[0], "env", ft_strlen("env")) == 0)
		return (2);
	if (ft_strncmp(node->cmd[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}

int		exec_builtin(t_env *env, t_node *node)
{
	if (is_builtin(node) == 0)
		return (0);
	if (is_builtin(node) == 7)
		ft_echo(node);
	if (is_builtin(node) == 6)
		ft_cd(node);
	if (is_builtin(node) == 5)
		ft_pwd(node);
	if (is_builtin(node) == 4)
		ft_export(env, node);
	if (is_builtin(node) == 3)
		ft_unset(node);
	if (is_builtin(node) == 2)
		ft_env(env);
	if (is_builtin(node) == 1)
		ft_exit(node);
	return (1);
}
