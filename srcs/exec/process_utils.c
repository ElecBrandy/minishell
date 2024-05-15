/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 00:58:04 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/15 19:06:44 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		count_node(t_node *node)
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

void redirect_io(int in_fd, int out_fd)
{
	if (in_fd != 0)
	{
		if (dup2(in_fd, 0) == -1)
		{
			exit(1); // Error
		}
		close(in_fd);
	}
	if (out_fd != 1)
	{
		if (dup2(out_fd, 1) == -1)
		{
			exit(1); // Error
		}
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
		i++;
	}
}

void close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}
