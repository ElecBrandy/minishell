/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:24:10 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/24 15:24:11 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		printf("\n");
	if (signal == SIGQUIT)
		printf("Quit: 3\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
}

void	heredoc_handler(int signal)
{
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
	g_signal_error = 1;
}
