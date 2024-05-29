/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:37 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 14:15:52 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	ft_echo
	- Print the arguments.
*/

static int	is_option(char *str);
static void	echo_without_option(t_node *node);
static void	echo_with_option(t_node *node);

void	ft_echo(t_node *node)
{
	int		i;
	int		n_flag;

	n_flag = FALSE;
	i = 1;
	if (ft_arrlen_2d(node->cmd) == 1)
		printf("\n");
	else
	{
		if (is_option(node->cmd[1]))
		{
			echo_with_option(node);
		}
		else
		{
			echo_without_option(node);
			printf("\n");
		}
	}
}

static void	echo_without_option(t_node *node)
{
	int	i;

	i = 1;
	while (node->cmd[i])
	{
		printf("%s", node->cmd[i]);
		if (node->cmd[i + 1])
			printf(" ");
		i++;
	}
}

static void	echo_with_option(t_node *node)
{
	int	i;

	i = 2;
	while (node->cmd[i] && is_option(node->cmd[i]))
		i++;
	while (node->cmd[i])
	{
		printf("%s", node->cmd[i]);
		if (node->cmd[i + 1])
			printf(" ");
		i++;
	}
}

static int	is_option(char *cmd)
{
	int	i;

	if (cmd[0] != '-' || cmd[1] != 'n')
		return (FALSE);
	i = 2;
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
