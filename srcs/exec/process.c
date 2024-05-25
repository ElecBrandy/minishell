/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:52:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/25 17:59:20 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_solo(t_env *head_env, t_node *node, int *cnt);
static void	child_normal(t_env *head_env, t_node *node, int *cnt);
static void	child_end(t_env *head_env, t_node *node, int *cnt);

void	fork_process(t_env *head_env, t_node *node, int node_cnt)
{
	int		i;
	int		fork_cnt;
	t_node	*cur;
	t_stdio	stdin_origin;

	fork_cnt = 0;
	cur = node;
	save_stdio(&stdin_origin);
	if (node_cnt == 0)		// 노드가 없는 경우
		return ;
	if (node_cnt == 1)		// pipe가 없는 경우
		child_solo(head_env, cur, &fork_cnt);
	else
	{
		i = 0;
		while (i < node_cnt - 1)
		{
			child_normal(head_env, cur, &fork_cnt);
			cur = cur->next;
			i++;
		}
		child_end(head_env, cur, &fork_cnt);
	}
	wait_process(fork_cnt);
	restore_stdio(&stdin_origin);
}


void	child_solo(t_env *head_env, t_node *node, int *cnt)
{
	pid_t	pid;

	if (is_builtin(node) != 0) // builtin 함수일 경우
	{
<<<<<<< HEAD
=======
		//fprintf(stderr, "child_solo\n");
>>>>>>> temp2
		redirect_io(node->in_fd, node->out_fd);
		exec_builtin(head_env, node);
	}
<<<<<<< HEAD
	else
	{
		pid = fork();
		if (pid == -1)
			exit(1); // Error
		if (pid == 0)
		{
			// printf("child_solo\n");
			redirect_io(node->in_fd, node->out_fd);
			// system("lsof -p $$ >> solo_log");
			run_cmd(head_env, node);
		}
		else
			(*cnt)++;
	}
=======
	(*cnt)++;
>>>>>>> temp2
}

static void	child_normal(t_env *head_env, t_node *node, int *cnt)
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
		dup2(fd[1], STDOUT); // 일단 출력을 fd[1]로 보내고
		close(fd[1]); // 닫고
		redirect_io(node->in_fd, node->out_fd); // 입출력을 재설정한다.
		close_pipe(fd);
		run_cmd(head_env, node);
	}
	else
	{
		(*cnt)++;
		dup2(fd[0], STDIN);
		close(fd[0]);
		close_pipe(fd);
	}
}

static void	child_end(t_env *head_env, t_node *node, int *cnt)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1);	// Error
	if (pid == 0)
	{
		redirect_io(node->in_fd, node->out_fd);
		run_cmd(head_env, node);
	}
	else
	{
		(*cnt)++;
	}
}
