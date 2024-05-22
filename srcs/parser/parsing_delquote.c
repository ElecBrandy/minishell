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
	t_util	u;
	char	**str;

	util_init(&u);
	u.cnt = count_str(av);
	str = malloc(sizeof(char *) * (u.cnt + 1));
	if (!str)
	{
		free_str(av);
		return (NULL);
	}
	str[u.cnt] = NULL;
	while (av[++u.i])
	{
		str[u.i] = del_quote(av[u.i]);
		if (!str[u.i])
		{
			free_str(av);
			free_str(str);
			return (NULL);
		}
	}
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
		if ((av[util.idx] == ' ' || av[util.idx] == '\t')
			&& (av[util.idx + 1] != ' ' && av[util.idx + 1] != '\t'))
		{
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
	if (!str[util.i])
	{
		free_str(str);
		return (NULL);
	}
	str[++util.i] = NULL;
	return (str);
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
	if (!str)
		return (NULL);
	u.i = -1;
	while (av[++u.i])
	{
		del_q(av, str, &u);
	}
	str[++u.idx] = '\0';
	return (str);
}
