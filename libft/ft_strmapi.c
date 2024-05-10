/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:39:43 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 14:57:23 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*word;
	int		i;

	i = 0;
	if (!s || !f)
		return ((void *)0);
	word = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!word)
		return ((void *)0);
	while (s[i])
	{
		word[i] = f((unsigned int)i, s[i]);
		i++;
	}
	word[i] = 0;
	return (word);
}
