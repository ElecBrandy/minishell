/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:12:41 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/25 12:32:28 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*word;
	char	*find;
	size_t	i;
	size_t	j;

	i = 0;
	word = (char *)haystack;
	find = (char *)needle;
	if (!find[i])
		return (word);
	while (word[i] && (i < len))
	{
		j = 0;
		while (find[j] && (word[i + j] == find[j]) && (i + j < len))
		{
			j++;
		}
		if (find[j] == '\0')
			return (word + i);
		i++;
	}
	return ((void *)0);
}
