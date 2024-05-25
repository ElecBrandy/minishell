/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:03 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/25 22:39:23 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		exit_withoutarg(t_env *head_env, t_node *node, pid_t pid);
static void		exit_witharg(t_env *head_env, t_node *node, pid_t pid);
static void		check_first_arg(t_node *node, long long *num, int *ll_flag, pid_t pid);
static int		is_numeric(char *str);
static void		ft_exit_error(char *str, int ll_flag, pid_t pid);

void    ft_exit(t_env *head_env, t_node *node, pid_t pid)
{
	char **tmp;

	if (ft_arrlen_2d(node->cmd) == 1)
		exit_withoutarg(head_env, node, pid);
	else
		exit_witharg(head_env, node, pid);
}

static void    exit_withoutarg(t_env *head_env, t_node *node, pid_t pid)
{
	ft_exit_error(NULL, 4, pid);
	free_env_list(head_env);
	exit(0);
}

static void    exit_witharg(t_env *head_env, t_node *node, pid_t pid)
{
	long long	num;
	int			ll_flag;

	ll_flag = TRUE;
	check_first_arg(node, &num, &ll_flag, pid);
	if (ft_arrlen_2d(node->cmd) > 2) // 3. 인자가 2개 이상인 경우
	{
		ft_exit_error(node->cmd[1], 2, pid);
	}
	else // 넘지 않을 경우 -> 부모에게 255 기준으로 나눠가며 전달 / 종료 o
	{
		ft_exit_error(NULL, 4, pid);
		exit(num % 256);
	}
	return ;
}

static void check_first_arg(t_node *node, long long *num, int *ll_flag, pid_t pid)
{
	char	**tmp;

	tmp = ft_split(node->cmd[1], ' ');
	if (ft_arrlen_2d(tmp) > 1) // 1. 첫번째 인자가 " 12342  241 " 일경우 -> 무조건 문자열로 취급해서 에러
	{
		ft_exit_error(node->cmd[1], 0, pid);
	}
	else // 2. 첫번째 인자가 최소한 "   3  "이라는 것.
	{
		
		*num = ft_strtoll(tmp[0], ll_flag);
		if (is_numeric(tmp[0]) == FALSE) // 첫번째 인자가 오로지 숫자 X
		{
			ft_exit_error(node->cmd[1], 0, pid);
		}
		else // 첫번째 인자가 오로시 숫자 O
		{
			if (*ll_flag == FALSE) // 2. 첫번째 인자가 LONG LONG 범위를 넘을 경우
			{
				ft_exit_error(node->cmd[1], 0, pid);
			}
		}
	}
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

static void ft_exit_error(char *str, int error_type, pid_t pid)
{
	if (pid == -2)
		ft_putstr_fd("exit\n", 2);
	if (str == NULL)
		return ;
	ft_putstr_fd("minishell: exit: ", 2);
	if (error_type == 0 || error_type == 1)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (error_type == 2)
	{
		ft_putstr_fd("too many arguments\n", 2);
		return ;
	}
}
