/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:29:40 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/29 20:32:43 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	print_error_latterhalf(void);
static int	print_error_firsthalf(void);

int	print_error(void)
{
	if (g_signal_error < 100)
	{
		print_error_firsthalf();
	}
	else if (g_signal_error >= 100)
	{
		print_error_latterhalf();
	}
	return (0);
}

static int	print_error_firsthalf(void)
{
	if (g_signal_error == 0)
		g_signal_error = 12;
	if (g_signal_error == -1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected end of file\n", 2);
		g_signal_error = 258;
	}
	else if (g_signal_error == -2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_signal_error = 258;
	}
	else if (g_signal_error == 1)
		return (0);
	else
	{
		errno = g_signal_error;
		perror("minishell");
	}
	return (0);
}

static int	print_error_latterhalf(void)
{
	if (g_signal_error == 127)
		return (0);
	else if (g_signal_error == 258)
		return (0);
	else if (g_signal_error == 126)
		return (0);
	else if (g_signal_error == 999)
		g_signal_error = 1;
	else
	{
		errno = g_signal_error;
		perror("minishell");
	}
	return (0);
}

void	syntax_error(char *str, t_node *node)
{
	g_signal_error = 258;
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (node->in_fd != 0)
		close(node->in_fd);
	if (node->out_fd != 1)
		close(node->out_fd);
	if (!str)
		ft_putstr_fd("`newline'\n", 2);
	else
	{
		if (str[0] == '<' && str[1] == '>')
			ft_putstr_fd("`<>'\n", 2);
		else if (str[0] == '<' && str[1] == '<')
			ft_putstr_fd("`<<'\n", 2);
		else if (str[0] == '<')
			ft_putstr_fd("`<'\n", 2);
		if (str[0] == '>' && str[1] == '>')
			ft_putstr_fd("`>>'\n", 2);
		else if (str[0] == '>')
			ft_putstr_fd("`>'\n", 2);
	}
}
