/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:53:40 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 15:58:27 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char			**ft_split(char const *s, char c);
static int		ft_count(char const *s, char c);
static int		ft_word(char **word, char const *s, char sep, int arr);
static void		ft_put_word(char *word, char const *s, char sep);
static void		ft_free(char **word, int cnt);

char	**ft_split(char const *s, char c)
{
	char	**word;
	int		cnt;
	int		arr;

	arr = 0;
	if (!s)
		return ((void *)0);
	cnt = ft_count(s, c);
	word = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (!word)
		return ((void *)0);
	if (ft_word(word, s, c, arr) == 1)
	{
		free(word);
		return ((void *)0);
	}
	word[cnt] = 0;
	return (word);
}

static int	ft_count(char const *s, char sep)
{
	int	i;
	int	cnt;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (!((s[i] == 0) || (s[i] == sep))
			&& (s[i + 1] == 0 || s[i + 1] == sep))
			cnt++;
		i++;
	}
	return (cnt);
}

static int	ft_word(char **word, char const *s, char sep, int arr)
{
	int	i;
	int	j;

	i = 0;
	while (i <= (int)ft_strlen(s))
	{
		j = 0;
		if (s[i] == 0 || s[i] == sep)
			i++;
		else
		{
			while (!(s[i + j] == 0 || s[i + j] == sep))
				j++;
			word[arr] = (char *)malloc(sizeof(char) * (j + 1));
			if (!word[arr])
			{
				ft_free(word, arr);
				return (1);
			}
			ft_put_word(word[arr++], s + i, sep);
			i += j;
		}
	}
	return (0);
}

static void	ft_put_word(char *word, char const *s, char sep)
{
	int	i;

	i = 0;
	while (!(s[i] == 0 || s[i] == sep))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
}

static void	ft_free(char **word, int cnt)
{
	int	i;

	i = 0;
	while (i <= cnt)
		free(word[i++]);
}
