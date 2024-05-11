/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/12 02:05:43 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_solo(t_env *env, t_node *node, int *cnt);
static void	child_normal(t_env *env, t_node *node, int *cnt);
static void	child_end(t_env *env, t_node *node, int *cnt);
// 일단 ; 제외하고... 생각ㅎ하기

void	fork_process(t_env *env, t_node *node, int node_cnt)
{
	int		fork_cnt;
	t_node	*cur;

	fork_cnt = 0;
	cur = node;
	fprintf(stderr, "node_cnt : %d\n", node_cnt);
	if (node_cnt == 0)		// 노드가 없는 경우
		return ;
	if (node_cnt == 1)		// pipe가 없는 경우
		child_solo(env, cur, &fork_cnt);
	else 					// pipe가 있는 경우
	{
		while (cur->next)
		{
			child_normal(env, cur, &fork_cnt);
			cur = cur->next;
		}
		child_end(env, cur, &fork_cnt);
		wait_process(fork_cnt);
	}
}

static void	child_solo(t_env *env, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1); // Error
	if (pid == 0)
	{
		redirect_io(node->in_fd, node->out_fd);
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
		redirect_io(node->in_fd, node->out_fd);
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		system("lsof -p $$ >> log");
		run_cmd(env, node);
	}
	else
	{
		(*cnt)++;
		dup2(fd[0], STDIN_FILENO);
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
		system("lsof -p $$ >> log");
		run_cmd(env, node);
	}
	else
		(*cnt)++;
}
