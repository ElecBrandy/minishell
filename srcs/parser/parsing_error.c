/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:43:24 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/21 19:27:39 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_numlen(int num)
{
	int	i;

	i = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

void	put_errno(char *str, int p_e, t_util *u)
{
	char	*word;
	int		i;

	i = -1;
	word = ft_itoa(p_e);
	while (word[++i])
		str[++(u->idx)] = word[i];
	(u->i) += 1;
	free(word);
}

int	file_error(void)
{
	if (!g_signal_error)
		return (12);
	return (g_signal_error);
}

void	notfile_error(char *file)
{
	printf("minishell: %s: %s\n", file, strerror(2));
	g_signal_error = 999;
}

char	*malloc_fail(void)
{
	g_signal_error = 12;
	return (NULL);
}
