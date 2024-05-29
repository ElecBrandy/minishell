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

int	check_pipeline(char ***str)
{
	int	i;
	int	j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j][0] == 0 && str[i][j + 1])
			{
				g_signal_error = -2;
				free_str_three(str);
				return (1);
			}
		}
	}
	return (0);
}

int	check_line(char **str)
{
	int	i;

	i = -1;
	if (str[0][0] == '|')
	{
		free_str(str);
		g_signal_error = -2;
		return (1);
	}
	while (str[++i] && str[i][0])
	{
		if (str[i][ft_strlen(str[i]) - 1] == '|')
		{
			free_str(str);
			g_signal_error = -1;
			return (1);
		}
	}
	return (0);
}

int	check_file_two(char *str, t_util *u)
{
	while (str[u->i] && str[u->i] != 34 && str[u->i] != 39)
	{
		if (u->flag == 2 && (str[u->i] != ' ' && str[u->i] != '\t'))
		{
			free(str);
			return (1);
		}
		else if (u->flag == 1 && (str[u->i] == ' ' || str[u->i] == '\t'))
			u->flag = 2;
		else if (str[u->i] != ' ' && str[u->i] != '\t')
			u->flag = 1;
		(u->i)++;
	}
	return (0);
}
