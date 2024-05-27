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

char	*save_in(char *av, t_util *util)
{
	char	*str;

	util->end = util->idx - 1;
	util->flag = util->idx;
	str = ft_strldup(av, util->start, util->end);
	str = ft_strtrim(str, " \t");
	if (!str)
		return (NULL);
	util->start = util->end + 2;
	return (str);
}

int	split_flag_save(char *av, char **str, t_util *u, char flag)
{
	while (av[++u->idx])
	{
		if (av[u->idx] == flag)
		{
			str[++u->i] = save_in(av, u);
			if (!str[u->i])
			{
				free_str(str);
				return (1);
			}
		}
		else
			u->idx = find_other(av, u->idx);
	}
	return (0);
}

char	**split_flag(char *av, int len, char flag)
{
	char	**str;
	t_util	u;

	util_init(&u);
	str = (char **)malloc(sizeof(char *) * (len + 2));
	if (!str)
		return (NULL);
	if (split_flag_save(av, str, &u, flag))
		return (NULL);
	if (u.flag == 0)
		str[++u.i] = save_in(av, &u);
	else
		str[++u.i] = save_in(av, &u);
	if (!str[u.i])
	{
		free_str(str);
		return (NULL);
	}
	str[++u.i] = NULL;
	return (str);
}

int	split_by_pipe(char **str_smc, char ***str_pipe)
{
	int	i;
	int	len;

	i = -1;
	while (str_smc[++i])
	{
		len = find_flag(str_smc[i], '|');
		str_pipe[i] = split_flag(str_smc[i], len, '|');
		if (!str_pipe[i])
		{
			free_str(str_smc);
			free_str_three(str_pipe);
			return (1);
		}
	}
	str_pipe[i] = NULL;
	return (0);
}

char	***parsing(char *av)
{
	int		len;
	char	**str_smc;
	char	***str_pipe;

	len = find_flag(av, ';');
	if (len == -1)
		return (NULL);
	str_smc = split_flag(av, len, ';');
	if (!str_smc || check_line(str_smc))
		return (NULL);
	str_pipe = malloc(sizeof(char **) * (len + 2));
	if (!str_pipe)
	{
		free_str(str_smc);
		return (NULL);
	}
	if (split_by_pipe(str_smc, str_pipe))
		return (NULL);
	if (check_pipeline(str_pipe))
	{
		free_str(str_smc);
		return (NULL);
	}
	free_str(str_smc);
	return (str_pipe);
}
