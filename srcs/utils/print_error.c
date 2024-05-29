/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 19:29:40 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/29 16:33:38 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error(void)
{
	if (g_signal_error == 0)
		g_signal_error = 12;
	if (g_signal_error == -1)
	{
		printf("minishell: syntax error near unexpected end of file\n");
		g_signal_error = 258;
	}
	if (g_signal_error == -2)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		g_signal_error = 258;
	}
	else if (g_signal_error == 127)
		return (0);
	else if (g_signal_error == 258)
		return (0);
	else if (g_signal_error == 126)
		return (0);
	else if (g_signal_error == 999)
		return (0);
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
	printf("minishell: syntax error near unexpected token ");
	if (node->in_fd != 0)
		close(node->in_fd);
	if (node->out_fd != 1)
		close(node->out_fd);
	if (!str)
		printf("`newline'\n");
	else
	{
		if (str[0] == '<' && str[1] == '>')
			printf("`<>'\n");
		else if (str[0] == '<' && str[1] == '<')
			printf("`<<'\n");
		else if (str[0] == '<')
			printf("`<'\n");
		if (str[0] == '>' && str[1] == '>')
			printf("`>>'\n");
		else if (str[0] == '>')
			printf("`>'\n");
	}
}
