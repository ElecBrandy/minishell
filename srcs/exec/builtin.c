/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:56:28 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:44:08 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	make_lower(char *str);

int	is_builtin(t_node *node)
{
	if (ft_strlen(node->cmd[0]) <= 0)
		return (0);
	if (ft_strlen(node->cmd[0]) == ft_strlen("exit") \
	&& ft_strncmp(node->cmd[0], "exit", ft_strlen(node->cmd[0])) == 0)
		return (1);
	if (ft_strlen(node->cmd[0]) == ft_strlen("export") \
	&& ft_strncmp(node->cmd[0], "export", ft_strlen(node->cmd[0])) == 0)
		return (4);
	if (ft_strlen(node->cmd[0]) == ft_strlen("unset") \
	&& ft_strncmp(node->cmd[0], "unset", ft_strlen(node->cmd[0])) == 0)
		return (3);
	make_lower(node->cmd[0]);
	if (ft_strlen(node->cmd[0]) == ft_strlen("echo") \
	&& ft_strncmp(node->cmd[0], "echo", ft_strlen(node->cmd[0])) == 0)
		return (7);
	if (ft_strlen(node->cmd[0]) == ft_strlen("cd") \
	&& ft_strncmp(node->cmd[0], "cd", ft_strlen(node->cmd[0])) == 0)
		return (6);
	if (ft_strlen(node->cmd[0]) == ft_strlen("pwd") \
	&& ft_strncmp(node->cmd[0], "pwd", ft_strlen(node->cmd[0])) == 0)
		return (5);
	if (ft_strlen(node->cmd[0]) == ft_strlen("env") \
	&& ft_strncmp(node->cmd[0], "env", ft_strlen(node->cmd[0])) == 0)
		return (2);
	return (0);
}

int	exec_builtin(t_env **env, t_node *node, pid_t pid)
{
	int	builtin;

	g_signal_error = 0;
	builtin = is_builtin(node);
	if (builtin == 0)
		return (0);
	if (builtin == 7)
		ft_echo(node);
	if (builtin == 6)
		ft_cd(env, node);
	if (builtin == 5)
		ft_pwd(*env, node);
	if (builtin == 4)
		ft_export(env, node);
	if (builtin == 3)
		ft_unset(env, node);
	if (builtin == 2)
		ft_env(*env, node);
	if (builtin == 1)
		ft_exit(*env, node, pid);
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
