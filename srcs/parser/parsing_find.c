/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:26:38 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/26 18:16:02 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_next_quote(char *av, int idx, char flag)
{
	while (av[++idx])
	{
		if (av[idx] == flag)
			return (idx);
	}
	return (-1);
}

int	find_other(char *av, int idx)
{
	if (av[idx] == 34)
		idx = find_next_quote(av, idx, 34);
	else if (av[idx] == 39)
		idx = find_next_quote(av, idx, 39);
	return (idx);
}

int	find_flag(char *av, char flag)
{
	int	idx;
	int	len;

	len = 0;
	idx = -1;
	while (av[++idx])
	{
		if (av[idx] == flag)
			len++;
		else if (av[idx] == 34)
			idx = find_next_quote(av, idx, 34);
		else if (av[idx] == 39)
			idx = find_next_quote(av, idx, 39);
		if (idx == -1)
		{
			g_signal_error = -1;
			return (-1);
		}
	}
	return (len);
}

int	find_cut(char *av)
{
	int	cut;
	int	i;

	i = -1;
	cut = 0;
	while (av[++i])
	{
		if (av[i] == 34)
		{
			i = find_next_quote(av, i, 34);
			cut += 2;
		}
		if (av[i] == 39)
		{
			i = find_next_quote(av, i, 39);
			cut += 2;
		}
	}
	return (cut);
}

int	find_env(char *av, int *idx, t_env *env)
{
	int		word_len;
	int		env_len;
	t_util	u;
	char	*word;
	t_env	*e;

	util_init(&u);
	e = env;
	word = get_word(av, idx);
	if (!word)
		return (-100);
	word_len = ft_strlen(word);
	while (e)
	{
		env_len = ft_max(word_len, ft_strlen(e->key));
		if (ft_strncmp(e->key, word, env_len) == 0)
		{
			u.cnt = ft_strlen(e->value) - word_len;
			u.cnt--;
			break ;
		}
		e = e->next;
	}
	free(word);
	return (u.cnt);
}
