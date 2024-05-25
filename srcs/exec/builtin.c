/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:56:28 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/25 17:33:43 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
echo with option -n : 7

cd with only a relative or absolute path : 6

pwd with no options : 5

export with no options : 4

unset with no options : 3

env with no options or arguments : 2

exit with no options : 1

no builtin : 0
*/

int		is_builtin(t_node *node)
{
	if (ft_strncmp(node->cmd[0], "echo", ft_strlen(node->cmd[0])) == 0) // 내부에서 -n 옵션 체크 하기
		return (7);
	if (ft_strncmp(node->cmd[0], "cd", ft_strlen(node->cmd[0])) == 0)
		return (6);
	if (ft_strncmp(node->cmd[0], "pwd", ft_strlen(node->cmd[0])) == 0 \
	|| ft_strncmp(node->cmd[0], "PWD", ft_strlen(node->cmd[0])) == 0) // 대문자 pwd?
		return (5);
	if (ft_strncmp(node->cmd[0], "export", ft_strlen(node->cmd[0])) == 0)
		return (4);
	if (ft_strncmp(node->cmd[0], "unset", ft_strlen(node->cmd[0])) == 0)
		return (3);
	if (ft_strncmp(node->cmd[0], "env", ft_strlen(node->cmd[0])) == 0)
		return (2);
	if (ft_strncmp(node->cmd[0], "exit", ft_strlen(node->cmd[0])) == 0)
		return (1);
	return (0);
}

int		exec_builtin(t_env *head_env, t_node *node)
{
	if (is_builtin(node) == 0)
		return (0);
	if (is_builtin(node) == 7)
		ft_echo(node);
	if (is_builtin(node) == 6)
		ft_cd(head_env, node);
	if (is_builtin(node) == 5)
		ft_pwd(node);
	if (is_builtin(node) == 4)
		ft_export(head_env, node);
	if (is_builtin(node) == 3)
		ft_unset(head_env, node);
	if (is_builtin(node) == 2)
		ft_env(head_env, node);
	if (is_builtin(node) == 1)
		ft_exit(head_env, node);
	return (1);
}
