/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:02:43 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/19 17:00:46 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*word;
	const char			*s;

	word = (unsigned char *)dst;
	s = src;
	if (!src && !dst)
		return ((void *)0);
	if (src >= dst)
	{
		while (len--)
			*word++ = *s++;
	}
	else
	{
		while (len--)
			*(word + len) = *(s + len);
	}
	return (dst);
}
