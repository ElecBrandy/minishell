/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 03:55:02 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/25 19:50:54 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_node_details(t_node *node)
{
	printf("Node details:\n");
	printf("Path: %s\n", node->path ? node->path : "None");
	printf("in_fd: %d, out_fd: %d\n", node->in_fd, node->out_fd);
	printf("Commands:\n");
	if (node->cmd)
	{
		for (int i = 0; node->cmd[i] != NULL; i++)
		{
			printf("  cmd[%d]: $%s$\n", i, node->cmd[i]);
		}
	}
	else
	{
		printf("  No commands\n");
	}
}

void print_linked_list(t_node *head)
{
	t_node *current = head;
	int index = 0;

	while (current != NULL)
	{
		printf("\n--- Node %d ---\n", index++);
		print_node_details(current);
		printf("\n");
		current = current->next;
	}
}



void print_env_list(t_env *head_env)
{
	t_env *cur;

	cur = head_env;
	while (cur)
	{
		fprintf(stderr, "cmd : %s\n", cur->cmd);
		fprintf(stderr, "key : %s\n", cur->key);
		fprintf(stderr, "value : %s\n", cur->value);
		fprintf(stderr, "\n");
		cur = cur->next;
	}
}

void	print_arry_2d(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		fprintf(stderr, "%s\n", arr[i]);
		i++;
	}
}


void head_env_chk(t_env *head_env, int i)
{
	if (head_env == NULL)
	{
		fprintf(stderr, "head_env is NULL\n");
		fprintf(stderr, "i : %d\n", i);
		exit(1); // Error
	}
}

void	print_process_log(void)
{
	pid_t pid = getpid();
	char command[256];
	snprintf(command, sizeof(command), "lsof -p %d >> log", pid);
	system(command);
}
