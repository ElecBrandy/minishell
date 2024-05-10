/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:42:36 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/07 16:57:50 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_node(char *env_line)
{
	t_env	*new_node;
	
	new_node = (t_env *)malloc(sizeof(t_env));
	if (new_node == NULL)
	{
		return (NULL); // Error
	}
	new_node->line = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node_backward(t_env **head, t_env *new_node)
{
	t_env	*current;

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

int		count_env_node(t_env *head)
{
	int		count;
	t_env	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
