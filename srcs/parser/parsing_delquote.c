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
		if (!str[u.i] && av[0])
		{
			free_str(av);
			free_str(str);
			return (NULL);
		}
	}
	free_str(av);
	return (str);
}

int	split_space_main(char *tmp, char **str, t_util *u)
{
	while (tmp[++(u->idx)])
	{
		if ((tmp[u->idx] == ' ' || tmp[u->idx] == '\t')
			&& (tmp[u->idx + 1] != ' ' && tmp[u->idx + 1] != '\t'))
		{
			str[++(u->i)] = save_in(tmp, u);
			if (!str[u->i])
			{
				free_str(str);
				return (1);
			}
		}
		else
		{
			u->idx = find_other(tmp, u->idx);
			if (u->idx == -1)
			{
				g_signal_error = -1;
				ft_free((void **)&tmp);
				free_all(str, u->i + 1);
				return (-1);
			}
		}
	}
	return (0);
}

char	**split_space(char *av, int len)
{
	char	**str;
	char	*tmp;
	t_util	u;

	util_init(&u);
	tmp = ft_strtrim(av, " \t");
	str = (char **)malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (NULL);
	if (split_space_main(tmp, str, &u))
		return (NULL);
	if (u.flag == 0)
		str[++u.i] = save_in(tmp, &u);
	else
		str[++u.i] = save_in(tmp, &u);
	ft_free((void **)&tmp);
	if (!str[u.i])
	{
		free_str(str);
		return (NULL);
	}
	str[++u.i] = NULL;
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
	{
		g_signal_error = 12;
		return (NULL);
	}
	u.i = -1;
	while (av[++u.i])
	{
		del_q(av, str, &u);
	}
	str[++u.idx] = '\0';
	return (str);
}
