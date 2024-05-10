/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:18:12 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 15:06:38 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*temp;
	t_list	*now;
	void	*ptr;

	if (!lst || !f || !del)
		return ((void *)0);
	now = lst;
	new_node = 0;
	while (now)
	{
		ptr = f(now->content);
		temp = ft_lstnew(ptr);
		if (!temp)
		{
			del(ptr);
			ft_lstclear(&new_node, del);
			return ((void *)0);
		}
		ft_lstadd_back(&new_node, temp);
		now = now->next;
	}
	return (new_node);
}
