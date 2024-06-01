/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:01:12 by dongeunk          #+#    #+#             */
/*   Updated: 2024/06/01 18:56:08 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*word;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return ((void *)0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	word = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!word)
		return ((void *)0);
	ft_memcpy(word, s1, len1);
	ft_memcpy(word + len1, s2, len2);
	word[len1 + len2] = 0;
	free(s1);
	return (word);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*word;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return ((void *)0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	word = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!word)
		return ((void *)0);
	ft_memcpy(word, s1, len1);
	ft_memcpy(word + len1, s2, len2);
	word[len1 + len2] = 0;
	return (word);
}
