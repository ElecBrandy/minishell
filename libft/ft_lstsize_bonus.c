/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:16:01 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 14:52:11 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst);

int	ft_lstsize(t_list *lst)
{
	t_list	*node;
	int		i;

	if (!lst)
		return (0);
	node = lst;
	i = 1;
	while (node->next)
	{
		i++;
		node = node->next;
	}
	return (i);
}
