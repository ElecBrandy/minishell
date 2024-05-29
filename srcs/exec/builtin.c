/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:56:28 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 14:04:25 by dongeunk         ###   ########.fr       */
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

static void	make_lower(char *str);

int	is_builtin(t_node *node)
{
	if (ft_strlen(node->cmd[0]) <= 0)
		return (0);//  Error -> exit code 0
	if (ft_strlen(node->cmd[0]) == ft_strlen("exit") \
	&& ft_strncmp(node->cmd[0], "exit", ft_strlen(node->cmd[0])) == 0) // 무조건 소문자만 인식
		return (1);
	if (ft_strlen(node->cmd[0]) == ft_strlen("export") \
	&& ft_strncmp(node->cmd[0], "export", ft_strlen(node->cmd[0])) == 0) // 무조건 소문자만 인식
		return (4);
	if (ft_strlen(node->cmd[0]) == ft_strlen("unset") \
	&& ft_strncmp(node->cmd[0], "unset", ft_strlen(node->cmd[0])) == 0) // 무조건 소문자만 인식
		return (3);
	make_lower(node->cmd[0]);
	if (ft_strlen(node->cmd[0]) == ft_strlen("echo") \
	&& ft_strncmp(node->cmd[0], "echo", ft_strlen(node->cmd[0])) == 0) // 대문자 소문자 인식, 섞여도 인식
		return (7);
	if (ft_strlen(node->cmd[0]) == ft_strlen("cd") \
	&& ft_strncmp(node->cmd[0], "cd", ft_strlen(node->cmd[0])) == 0) // 대문자 소문자 인식, 섞여도 인식
		return (6);
	if (ft_strlen(node->cmd[0]) == ft_strlen("pwd") \
	&& ft_strncmp(node->cmd[0], "pwd", ft_strlen(node->cmd[0])) == 0) // 대문자 소문자 인식, 섞여도 인식
		return (5);
	if (ft_strlen(node->cmd[0]) == ft_strlen("env") \
	&& ft_strncmp(node->cmd[0], "env", ft_strlen(node->cmd[0])) == 0) // 대문자 소문자 인식, 섞여도 인식
		return (2);
	return (0);
}

int	exec_builtin(t_env **head_env, t_node *node, char *home, pid_t pid)
{
	int	builtin;

	builtin = is_builtin(node);
	if (builtin == 0)
		return (0);
	if (builtin == 7)
		ft_echo(node);
	if (builtin == 6)
		ft_cd(*head_env, node, home);  // head_env가 수정될 필요가 없다면, *head_env 사용
	if (builtin == 5)
		ft_pwd(node);
	if (builtin == 4)
		ft_export(*head_env, node);   // 마찬가지로 *head_env 사용
	if (builtin == 3)
		ft_unset(head_env, node);    // *head_env로 수정 필요
	if (builtin == 2)
		ft_env(*head_env, node);
	if (builtin == 1)
		ft_exit(*head_env, node, pid);
	return (1);
}

static void	make_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}
