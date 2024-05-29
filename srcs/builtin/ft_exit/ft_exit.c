/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:03 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 17:45:18 by dongwook         ###   ########.fr       */
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

static int	exit_withoutarg(t_env *head_env);
static int	exit_witharg(t_node *node, pid_t pid);
static void	ft_exit_error(int error, char *str);

void	ft_exit(t_env *head_env, t_node *node, pid_t pid)
{
	int		error;

	if (ft_arrlen_2d(node->cmd) == 1)
	{
		error = exit_withoutarg(head_env);
		if (pid < 0)
			ft_putstr_fd("exit\n", 2);
		exit(error);
	}
	else
	{
		error = exit_witharg(node, pid);
		if (error == 0)
			exit(error);
		else
			ft_exit_error(error, node->cmd[1]);
	}
}

static int	exit_withoutarg(t_env *head_env)
{
	free_env_list(head_env);
	return (0);
}

static int	exit_witharg(t_node *node, pid_t pid)
{
	long long	num;
	int			error;
	int			ll_flag;

	if (pid < 0)
		ft_putstr_fd("exit\n", 1);
	ll_flag = TRUE;
	error = check_first_arg(node, &num, &ll_flag);
	if (error != 0)
		return (error);
	if (ft_arrlen_2d(node->cmd) > 2)
		return (2);
	return (num % 256);
}

static void	ft_exit_error(int error, char *str)
{
	if (error == 1)
	{
		g_signal_error = 255;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
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
		exit(g_signal_error);
	}
	else
	{
		g_signal_error = error;
		exit(g_signal_error);
	}
}
