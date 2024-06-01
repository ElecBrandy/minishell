/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:03 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:13:11 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	ft_exit
	- Exit the shell.
	- If there is no argument, exit the shell with the return value of the exit.
	- If there is an argument, exit the shell with the argument.

	error_log
	- 0 : Success
	- 1 : minishell: exit: numeric argument required (shell exited)
	- 2 : minishell: exit: too many arguments (shell not exited)
	- 12 : malloc error (shell not exited)
	- ex : perror (shell exited)
*/

static int	exit_witharg(t_node *node, int *error);
static void	ft_exit_error(int error, char *str, t_env *env);

void	ft_exit(t_env *env, t_node *node, pid_t pid)
{
	int	error;
	int	result;

	error = 0;
	result = 0;
	if (ft_arrlen_2d(node->cmd) > 1)
		result = exit_witharg(node, &error);
	if (pid < 0)
		ft_putstr_fd("exit\n", 2);
	if (error != 0)
		ft_exit_error(error, node->cmd[1], env);
	else
	{
		g_signal_error = result;
		free_env_list(env);
		exit(g_signal_error);
	}	
}

static int	exit_witharg(t_node *node, int *error)
{
	long long	num;

	num = check_first_arg(node, error);
	if (*error != 0)
		return (0);
	if (ft_arrlen_2d(node->cmd) > 2)
		*error = 2;
	return (num % 256);
}

static void	ft_exit_error(int error, char *str, t_env *env)
{
	if (error == 1)
	{
		g_signal_error = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_env_list(env);
		exit(g_signal_error);
	}
	else if (error == 2)
	{
		g_signal_error = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else if (error == 12)
	{
		g_signal_error = 12;
		print_error();
		free_env_list(env);
		exit(g_signal_error);
	}
	else
	{
		g_signal_error = error;
		free_env_list(env);
		exit(g_signal_error);
	}
}
