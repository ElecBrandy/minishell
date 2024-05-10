/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:26:27 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 17:52:53 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_cmd_node(void)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (new_node == NULL)
	{
		return (NULL); // Error
	}
	new_node->cmd = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_cmd_node_backward(t_node **head, t_node *new_node)
{
	t_node	*current;

    if (*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

int		count_node_node(t_node *head)
{
	int		count;
	t_node	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
