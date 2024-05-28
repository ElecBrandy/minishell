/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/27 18:54:01 by dongeunk         ###   ########.fr       */
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

	if (!node->cmd[0])
		return (0);
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
			run_cmd(head_env, node, home, pid);
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
		run_cmd(head_env, node, home, pid);
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
		run_cmd(head_env, node, home, pid);
	}
	else
		(*cnt)++;
}

static void	is_inchild(char *cmd)
{
	
	if (ft_strncmp(cmd, "./", 2))
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
	}
}
