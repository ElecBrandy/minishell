/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:26:19 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:45:15 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else if (a < b)
		return (b);
	return (a);
}

int	get_flagcnt(char *av)
{
	t_util	u;

	util_init(&u);
	while (av[++u.i])
	{
		if (av[u.i] == 34)
			u.i = find_next_quote(av, u.i, 34);
		else if (av[u.i] == 39)
			u.i = find_next_quote(av, u.i, 39);
		if ((av[u.i] == '<' || av[u.i] == '>')
			&& (av[u.i + 1] != '<' && av[u.i + 1] != '>' && av[u.i + 1] != ' '))
			u.flag++;
	}
	return (u.flag);
}

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
			g_errnum = -1;
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
