/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 03:55:02 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/12 04:00:22 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_node_details(t_node *node)
{
	printf("Node details:\n");
	printf("Path: %s\n", node->path ? node->path : "None");
	printf("in_fd: %d, out_fd: %d\n", node->in_fd, node->out_fd);

	printf("Commands:\n");
	if (node->cmd)
	{
		for (int i = 0; node->cmd[i] != NULL; i++)
		{
			printf("  cmd[%d]: %s\n", i, node->cmd[i]);
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
