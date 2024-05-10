/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 13:36:34 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/26 14:10:46 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n);

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	while ((*(a + i) || *(b + i)) && i < n)
	{
		if (*(a + i) < *(b + i))
			return (*(a + i) - *(b + i));
		else if (*(a + i) > *(b + i))
			return (*(a + i) - *(b + i));
		i++;
	}
	return (0);
}
