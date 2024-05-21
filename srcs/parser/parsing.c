/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:26:10 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/12 02:42:23 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_other(char *av, int idx)
{
	if (av[idx] == 34)
		idx = find_next_quote(av, idx, 34);
	else if (av[idx] == 39)
		idx = find_next_quote(av, idx, 39);
	return (idx);
}

char	*save_in(char *av, t_util *util)
{
	char	*str;

	util->end = util->idx - 1;
	util->flag = util->idx;
	str = ft_strldup(av, util->start, util->end);
	str = ft_strtrim(str, " ");
	if (!str)
		return (NULL);
	util->start = util->end + 2;
	return (str);
}

char	**split_flag(char *av, int len, char flag)
{
	char	**str;
	t_util	util;

	util_init(&util);
	str = (char **)malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (NULL);
	while (av[++util.idx])
	{
		if (av[util.idx] == flag)
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

char	***parsing(char *av)
{
	int		len;
	int		i;
	char	**str_smc;
	char	***str_pipe;

	len = find_flag(av, ';');
	if (len == -1)
		return (NULL);
	str_smc = split_flag(av, len, ';');
	if (!str_smc)
		return (NULL);
	str_pipe = malloc(sizeof(char **) * (len + 2));
	if (!str_pipe)
	{
		free_str(str_smc);
		return (NULL);
	}
	i = -1;
	while (str_smc[++i])
	{
		len = find_flag(str_smc[i], '|');
		str_pipe[i] = split_flag(str_smc[i], len, '|');
		if (!str_pipe[i])
		{
			free_str(str_smc);
			free_str_three(str_pipe);
			return (NULL);
		}
	}
	free_str(str_smc);
	str_pipe[i] = NULL;
	return (str_pipe);
}
