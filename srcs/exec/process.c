/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 17:02:21 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_solo(t_env **env, t_node *node, int *cnt);
static void	child_normal(t_env **env, t_node *node, int *cnt);
static void	child_end(t_env **env, t_node *node, int *cnt);

int	processing(t_env **env, t_node *head)
{
	int	i;

	i = count_node(head);
	fork_process(env, head, i);
	return (0);
}

void	fork_process(t_env **env, t_node *node, int node_cnt)
{
	t_util	u;
	t_node	*cur;
	t_stdio	stdin_origin;

	if (!node->cmd[0] || node->cmd[0][0] == 0)
		return ;
	util_init(&u);
	cur = node;
	save_stdio(&stdin_origin);
	g_signal_error = find_path(cur->cmd[0], (*env), cur);
	if (node_cnt == 1)
		child_solo(env, cur, &u.cnt);
	else
	{
		while (++u.i < node_cnt - 1)
		{
			child_normal(env, cur, &u.cnt);
			cur = cur->next;
			g_signal_error = find_path(cur->cmd[0], (*env), cur);
		}
		child_end(env, cur, &u.cnt);
	}
	restore_stdio(&stdin_origin);
	wait_process(u.cnt);
}

static void	child_solo(t_env **env, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = -2;
	if (is_builtin(node) != 0)
	{
		redirect_io(node->in_fd, node->out_fd);
		exec_builtin(env, node, pid);
	}
	else
	{
		pid = fork();
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		is_inchild(node->cmd[0]);
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			redirect_io(node->in_fd, node->out_fd);
			ft_execve(env, node, pid);
		}
		(*cnt)++;
	}
}

static void	child_normal(t_env **env, t_node *node, int *cnt)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	is_inchild(node->cmd[0]);
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[1]);
		redirect_io(node->in_fd, node->out_fd);
		close_pipe(fd);
		ft_execve(env, node, pid);
	}
	(*cnt)++;
	dup2(fd[0], STDIN);
	close(fd[0]);
	close_pipe(fd);
}

static void	child_end(t_env **env, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	is_inchild(node->cmd[0]);
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		redirect_io(node->in_fd, node->out_fd);
		ft_execve(env, node, pid);
	}
	(*cnt)++;
}
