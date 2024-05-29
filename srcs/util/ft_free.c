/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:14:34 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/28 18:39:40 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int	i;

	i = 0;
	while (str[i])
	{
		ft_free((void **)&str[i]);
		i++;
	}
	ft_free((void **)&str);
}
