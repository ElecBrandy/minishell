/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:15:37 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/03 15:16:49 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_find_quotes(const char *s, int c)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			flag++;
	}
	return (flag);
}
