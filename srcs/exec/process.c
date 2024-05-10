/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 17:52:53 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void close_pipe(int *fd);
static void	wait_process(int cnt);
static void	child_solo(t_env *env_head, t_node *first_node, int *cnt);
static void	child_normal(t_env *env_head, t_node *node, int *cnt);
static void	child_end(t_env *env_head, t_node *node, int *cnt);
// 일단 ; 제외하고... 생각ㅎ하기

void	fork_process(t_env *env_head, t_node *node_head, int node_cnt)
{
	int		fork_cnt;
	t_node	*cur;

	fork_cnt = 0;
	cur = node_head->next;	// 첫번째 노드(헤드니까)
	if (node_cnt == 0)		// 노드가 없는 경우
		return ;
	if (node_cnt == 1)		// pipe가 없는 경우
		child_solo(env_head, cur, &fork_cnt);
	else 					// pipe가 있는 경우
	{
		while (cur->next)
		{
			child_normal(env_head, cur, &fork_cnt);
			cur = cur->next;
		}
		child_end(env_head, cur, &fork_cnt);
		wait_process(fork_cnt);
	}
}

static void	child_solo(t_env *env_head, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1); // Error
	if (pid == 0)
		run_cmd(env_head, node);
	else
		(*cnt)++;
}

static void	child_normal(t_env *env_head, t_node *node, int *cnt)
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
		dup2(fd[1], STDOUT_FILENO);
		close_pipe(fd);
		run_cmd(env_head, node);
	}
	else
	{
		(*cnt)++;
		dup2(fd[0], STDIN_FILENO);
		close_pipe(fd);
	}
}

static void	child_end(t_env *env_head, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);	// Error
	if (pid == 0)
	{
		// system("lsof -p $$ >> log");
		run_cmd(env_head, node);
	}
	else
		(*cnt)++;
}

static	void	wait_process(int cnt)
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

static void close_pipe(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}