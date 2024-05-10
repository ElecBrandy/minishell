/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:29:20 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 15:59:00 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			*ft_itoa(int n);
static int		ft_getlen(int n);

char	*ft_itoa(int n)
{
	char	*word;
	int		len;
	int		i;

	i = 0;
	len = ft_getlen(n);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return ((void *)0);
	word[len--] = 0;
	if (n < 0)
	{
		word[0] = '-';
		i++;
	}
	while (len >= i)
	{
		if (n < 0)
			word[len--] = (n % 10) * (-1) + 48;
		else
			word[len--] = (n % 10) + 48;
		n /= 10;
	}
	return (word);
}

static int	ft_getlen(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}
