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

void	util_init(t_util *util)
{
	util->i = -1;
	util->start = 0;
	util->end = 0;
	util->idx = -1;
	util->flag = 0;
	util->j = -1;
	util->cnt = 0;
}

int	find_next_quote(char *av, int idx, char flag)
{
	while (av[++idx])
	{
		if (av[idx] == flag)
			return (idx);
	}
	// 따옴표가 안닫혀있으면 에러처리
	printf("error\n");
	exit (1);
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
	}
	return (len);
}

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
