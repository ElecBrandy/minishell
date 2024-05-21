/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_delquote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:23:22 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/16 18:23:50 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**check_cmd(char **av)
{
	int		i;
	char	**str;

	i = 0;
	while (av[i])
		i++;
	str = malloc(sizeof(char *) * (i + 1));
	str[i] = NULL;
	i = -1;
	while (av[++i])
		str[i] = del_quote(av[i]);
	free_str(av);
	return (str);
}

char	**split_space(char *av, int len)
{
	char	**str;
	t_util	util;

	util_init(&util);
	str = (char **)malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (NULL);
	while (av[++util.idx])
	{
		if (av[util.idx] == ' ')
		{
			if (av[util.idx + 1] != ' ')
				str[++util.i] = save_in(av, &util);
			if (!str[util.i])
			{
				free_str(str);
				return (NULL);
			}
		}
		else
			util.idx = find_other(av, util.idx);
	}
	if (util.flag == 0)
		str[++util.i] = save_in(av, &util);
	else
		str[++util.i] = save_in(av, &util);
	str[++util.i] = NULL;
	return (str);
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

void	del_q(char *av, char *str, t_util *u)
{
	if (av[u->i] == 39)
	{
		if (u->flag == 0)
			u->flag = 1;
		else if (u->flag == 3)
			str[++(u->idx)] = av[u->i];
		else
			u->flag = 0;
	}
	else if (av[u->i] == 34)
	{
		if (u->flag == 0)
			u->flag = 3;
		else if (u->flag == 1)
			str[++(u->idx)] = av[u->i];
		else
			u->flag = 0;
	}
	else
		str[++(u->idx)] = av[u->i];
}

char	*del_quote(char *av)
{
	t_util	u;
	int		cut;
	char	*str;

	cut = find_cut(av);
	util_init(&u);
	str = malloc(sizeof(char) * (ft_strlen(av) - cut + 1));
	u.i = -1;
	while (av[++u.i])
	{
		del_q(av, str, &u);
	}
	str[++u.idx] = '\0';
	return (str);
}
