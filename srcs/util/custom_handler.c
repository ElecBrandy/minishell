/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:24:10 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/26 20:17:15 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
	g_signal_error = 1;
}

void	child_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		if (g_signal_error == 0)
			g_signal_error = -4;
	}
	else if (signal == SIGQUIT)
	{
		printf("Quit: 3\n");
		if (g_signal_error == 0)
			g_signal_error = -5;
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		if (rl_on_new_line() == -1)
			exit(1);
		rl_replace_line("", 1);
		g_signal_error = 1;
		exit (g_signal_error);
	}
}
