/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:30:10 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/05 17:30:56 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	ft_strcpy(char *dest, char *src, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		dest[i] = src[start];
		i++;
		start++;
	}
	dest[i] = '\0';
}

char	*ft_strldup(char *s1, int start, int end)
{
	int		i;
	char	*dest;
	char	*src;

	src = s1;
	i = end - start;
	dest = (char *)malloc(sizeof(char) * (i + 1));
	if (!dest)
		return (0);
	ft_strcpy(dest, src, start, end);
	return (dest);
}
