/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 00:58:04 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 17:48:30 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_node(t_node *node)
{
	int		cnt;
	t_node	*cur;

	cnt = 0;
	cur = node;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	return (cnt);
}

void	redirect_io(int in_fd, int out_fd)
{
	if (in_fd != STDIN)
	{
		if (dup2(in_fd, STDIN) == -1)
			exit(1);
		close(in_fd);
	}
	if (out_fd != STDOUT)
	{
		if (dup2(out_fd, STDOUT) == -1)
			exit(1);
		close(out_fd);
	}
}

void	wait_process(int cnt)
{
	int	status;
	int	i;

	i = 0;
	while (i < cnt)
	{
		wait(&status);
		if (g_signal_error == -4)
			g_signal_error = 130;
		else if (g_signal_error == -5)
			g_signal_error = 131;
		else
			g_signal_error = WEXITSTATUS(status);
		i++;
	}
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
