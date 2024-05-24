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

int	check_line(char ***str)
{
	int	i;
	int	j;

	i = -1;
	if (str[0][0][0] == 0)
	{
		free_str_three(str);
		g_signal_error = -2;
		return (1);
	}
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j][0] == 0)
			{
				free_str_three(str);
				g_signal_error = -1;
				return (1);
			}				
		}
	}
	return (0);
}
