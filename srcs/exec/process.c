/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/15 20:01:07 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_solo(t_env *env, t_node *node, int *cnt);
static void	child_normal(t_env *env, t_node *node, int *cnt);
static void	child_end(t_env *env, t_node *node, int *cnt);

void	fork_process(t_env *env, t_node *node, int node_cnt)
{
	int		i;
	int		stdin_origin;
	int		stdout_origin;
	int		fork_cnt;
	t_node	*cur;

	fork_cnt = 0;
	cur = node;
	stdin_origin = dup(STDIN);
	stdin_origin = dup(STDOUT);
	if (node_cnt == 0)		// 노드가 없는 경우
		return ;
	if (node_cnt == 1)		// pipe가 없는 경우
		child_solo(env, cur, &fork_cnt);
	else 					// pipe가 있는 경우
	{
		i = 0;
		while (i < node_cnt - 1)
		{
			child_normal(env, cur, &fork_cnt);
			cur = cur->next;
			i++;
		}
		child_end(env, cur, &fork_cnt);
		// fprintf(stderr, "fork_cnt : %d\n", fork_cnt);
	}
	dup2(stdin_origin, STDIN);
	dup2(stdout_origin, STDOUT);
	printf("fork_cnt : %d\n", fork_cnt);
	wait_process(fork_cnt);
	// system("lsof -p $$ >> parents_log");
	// printf("==========fork_process_end==========\n");
}

static void	child_solo(t_env *env, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1); // Error
	if (pid == 0)
	{
		// fprintf(stderr, "child_solo\n");
		redirect_io(node->in_fd, node->out_fd);
		system("lsof -p $$ >> log");
		// system("lsof -p $$ >> solo_log");
		run_cmd(env, node);
	}
	else
		(*cnt)++;
}

static void	child_normal(t_env *env, t_node *node, int *cnt)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(1);	// Error
	pid = fork();
	if (pid == -1)
		exit(1);	// Error
	if (pid == 0)
	{
		// fprintf(stderr, "child_normal\n");
		// printf("node->in_fd : %d\n", node->in_fd);
		// printf("node->out_fd : %d\n", node->out_fd);
		// redirect_io(node->in_fd, node->out_fd);
		dup2(fd[1], STDOUT);
		close_pipe(fd);
		system("lsof -p $$ >> log");
		run_cmd(env, node);
	}
	else
	{
		(*cnt)++;
		dup2(fd[0], STDIN);
		close_pipe(fd);
	}
}

static void	child_end(t_env *env, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);	// Error
	if (pid == 0)
	{
		// fprintf(stderr, "child_end\n");
		// redirect_io(node->in_fd, node->out_fd);
		system("lsof -p $$ >> log");
		run_cmd(env, node);
	}
	else
	{
		(*cnt)++;
	}
}
