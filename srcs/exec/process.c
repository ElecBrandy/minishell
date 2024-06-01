/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 20:16:06 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_solo(t_env **env, t_node *node, char *home, int *cnt);
static void	child_normal(t_env **env, t_node *node, char *home, int *cnt);
static void	child_end(t_env **env, t_node *node, char *home, int *cnt);

int	processing(t_env **env, t_node *head, char *home)
{
	int	i;

	i = count_node(head);
	fork_process(env, head, home, i);
	return (0);
}

int	fork_process(t_env **env, t_node *node, char *home, int node_cnt)
{
	t_util	u;
	t_node	*cur;
	t_stdio	stdin_origin;

	if (!node->cmd[0] || node->cmd[0][0] == 0)
		return (0);
	util_init(&u);
	cur = node;
	save_stdio(&stdin_origin);
	g_signal_error = find_path(cur->cmd[0], (*env), cur);
	if (node_cnt == 1)
		child_solo(env, cur, home, &u.cnt);
	else
	{
		while (++u.i < node_cnt - 1)
		{
			child_normal(env, cur, home, &u.cnt);
			cur = cur->next;
			g_signal_error = find_path(cur->cmd[0], (*env), cur);
		}
		child_end(env, cur, home, &u.cnt);
	}
	wait_process(u.cnt);
	restore_stdio(&stdin_origin);
	return (0);
}

void	child_solo(t_env **env, t_node *node, char *home, int *cnt)
{
	pid_t	pid;

	pid = -2;
	if (is_builtin(node) != 0)
	{
		redirect_io(node->in_fd, node->out_fd);
		exec_builtin(env, node, home, pid);
	}
	else
	{
		pid = fork();
		signal(SIGINT, SIG_IGN);
		is_inchild(node->cmd[0]);
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			redirect_io(node->in_fd, node->out_fd);
			ft_execve(env, node, home, pid);
		}
		(*cnt)++;
	}
}

static void	child_normal(t_env **env, t_node *node, char *home, int *cnt)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	is_inchild(node->cmd[0]);
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		dup2(fd[1], STDOUT);
		close(fd[1]);
		redirect_io(node->in_fd, node->out_fd);
		close_pipe(fd);
		ft_execve(env, node, home, pid);
	}
	else
	{
		(*cnt)++;
		dup2(fd[0], STDIN);
		close(fd[0]);
		close_pipe(fd);
	}
}

static void	child_end(t_env **env, t_node *node, char *home, int *cnt)
{
	pid_t	pid;
	
	pid = fork();
	signal(SIGINT, SIG_IGN);
	is_inchild(node->cmd[0]);
	if (pid == -1)
		exit(1);
	if (pid == 0)
	{
		redirect_io(node->in_fd, node->out_fd);
		ft_execve(env, node, home, pid);
	}
	else
		(*cnt)++;
}
