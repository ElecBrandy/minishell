/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:19:32 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 16:37:14 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_substr(char const *s, unsigned int start, size_t len);
static int	ft_getcnt(unsigned int size, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*word;
	unsigned int	size;
	unsigned int	i;
	unsigned int	cnt;

	i = 0;
	if (!s)
		return (0);
	size = ft_strlen(s);
	cnt = (unsigned int)ft_getcnt(size, start, len);
	word = (char *)malloc(sizeof(char) * (cnt + 1));
	if (!word)
		return ((void *)0);
	while ((start < size) && (i < len))
	{
		word[i++] = s[start++];
	}
	word[i] = 0;
	return (word);
}

static int	ft_getcnt(unsigned int size, unsigned int start, size_t len)
{
	if (size <= start)
		return (0);
	if (size >= len)
	{
		if (len < size - start)
			return (len);
		return (size - start);
	}
	return (size - start);
}
