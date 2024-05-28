/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/28 17:04:07 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_solo(t_env *head_env, t_node *node, char *home, int *cnt);
static void	child_normal(t_env *head_env, t_node *node, char *home, int *cnt);
static void	child_end(t_env *head_env, t_node *node, char *home, int *cnt);
static void	is_inchild(char *cmd);

int	fork_process(t_env *head_env, t_node *node, char *home, int node_cnt)
{
	t_util	u;
	t_node	*cur;
	t_stdio	stdin_origin;

	util_init(&u);
	cur = node;
	save_stdio(&stdin_origin);
	if (node_cnt == 1)
		child_solo(head_env, cur, home, &u.cnt);
	else
	{
		while (++u.i < node_cnt - 1)
		{
			child_normal(head_env, cur, home, &u.cnt);
			cur = cur->next;
		}
		child_end(head_env, cur, home, &u.cnt);
	}
	wait_process(u.cnt);
	restore_stdio(&stdin_origin);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

void	child_solo(t_env *head_env, t_node *node, char *home, int *cnt)
{
	pid_t	pid;

	pid = -2;
	if (is_builtin(node) != 0)
	{
		redirect_io(node->in_fd, node->out_fd);
		exec_builtin(head_env, node, home, pid);
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
			ft_execve(head_env, node, home, pid);
		}
		(*cnt)++;
	}
}

static void	child_normal(t_env *head_env, t_node *node, char *home, int *cnt)
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
		ft_execve(head_env, node, home, pid);
	}
	else
	{
		(*cnt)++;
		dup2(fd[0], STDIN);
		close(fd[0]);
		close_pipe(fd);
	}
}

static void	child_end(t_env *head_env, t_node *node, char *home, int *cnt)
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
		ft_execve(head_env, node, home, pid);
	}
	else
		(*cnt)++;
}

static void	is_inchild(char *cmd)
{
	int	flag;

	flag = 0;
	if (strncmp(cmd, "cat", 3) == 0)
		flag = 1;
	else if (strncmp(cmd, "/bin/cat", 8) == 0)
		flag = 1;
	else if (strncmp(cmd, "wc", 2) == 0)
		flag = 1;
	else if (strncmp(cmd, "/usr/bin/wc", 10) == 0)
		flag = 1;
	else if (strncmp(cmd, "sed", 3) == 0)
		flag = 1;
	else if (strncmp(cmd, "/usr/bin/sed", 12) == 0)
		flag = 1;
	if (flag == 1)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
}
