/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:03 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/25 18:35:13 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exit_withoutarg(t_env *head_env, t_node *node);
static void		exit_witharg(t_env *head_env, t_node *node);
static int		is_numeric(char *str);
static void		ft_exit_error(char *str, int signal);

void    ft_exit(t_env *head_env, t_node *node)
{
	if (ft_arrlen_2d(node->cmd) == 1)
	{
		exit_withoutarg(head_env, node);
	}
	else // 인자가 있는 경우
	{
		exit_witharg(head_env, node);
	}
}

static void    exit_withoutarg(t_env *head_env, t_node *node)
{
	ft_exit_error(NULL, 4);
	free_env_list(head_env);
	exit(0);
}

static void    exit_witharg(t_env *head_env, t_node *node)
{
	long long	num;
	int			signal;

	signal = TRUE;
	if (is_numeric(node->cmd[1]) == FALSE) // 1. 첫번째 인자가 숫자가 아닌 경우
	{
		ft_exit_error(node->cmd[1], 0);
		exit(255);
	}
	num = ft_strtoll(node->cmd[1], &signal);
	if (signal == FALSE) // 2. 첫번째 인자가 LONG LONG 범위를 넘을 경우
	{
		ft_exit_error(node->cmd[1], 1);
		exit(255);
	}
	if (ft_arrlen_2d(node->cmd) > 2) // 3. 인자가 2개 이상인 경우
	{
		ft_exit_error(node->cmd[1], 2);
		return ; // Error : echo $? -> 1
	}
	else // 넘지 않을 경우 -> 부모에게 255 기준으로 나눠가며 전달 / 종료 o
	{
		ft_exit_error(NULL, 4);
		exit(num % 256);
	}
	return ;
}

static int	is_numeric(char *str)
{
	if (str[0] == '-') // 음수일 경우
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

static void	ft_exit_error(char *str, int signal)
{
	if (str == NULL)
		ft_putstr_fd("exit\n", 2);
	else
	{
		if (signal == 0)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		else if (signal == 1)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
		}
		else if (signal == 2)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd("too many arguments\n", 2);
		}
	}
}
