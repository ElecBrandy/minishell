/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:14:34 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/08 16:59:53 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void **target)
{
	if (target != NULL && (*target) != NULL)
	{
		free(*target);
		*target = NULL;
	}
}
void	ft_free_2d(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_free((void **)&str[i]);
		i++;
	}
	ft_free((void **)&str);
}