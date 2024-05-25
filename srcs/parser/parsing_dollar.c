/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:29:18 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/16 19:13:39 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_dollar(char *av, char *str, t_util *u)
{
	u->cnt = 1;
	str[++(u->idx)] = av[u->i];
	while (av[++(u->i)])
	{
		if (av[u->i] != ' ')
			break ;
		str[++(u->idx)] = av[u->i];
	}
	if (av[u->i] == '\0')
		return ;
	str[++(u->idx)] = av[u->i];
	while (av[++(u->i)])
	{
		if (av[u->i] == ' ')
			break ;
		str[++(u->idx)] = av[u->i];
	}
	if (av[u->i] == '\0')
		return ;
	str[++(u->idx)] = av[u->i];
}

char	*change_dollar(char *av, t_env *env, int env_len, int p_e)
{
	t_util	u;
	char	*str;

	util_init(&u);
	u.cnt = ft_strlen(av);
	u.flag = p_e;
	str = malloc(sizeof(char) * (u.cnt + env_len + 1));
	if (!str)
		return (NULL);
	while (av[++u.i])
	{
		if (u.i > 0 && (av[u.i] == '<' && av[u.i - 1] == '<'))
			u.cnt = 0;
		if (u.cnt == 0)
			put_dollar(av, str, &u);
		else
			put_change_dollar(av, str, env, &u);
		if (av[u.i] == '\0')
			break ;
	}
	str[++u.idx] = '\0';
	return (str);
}

char	*check_dollar(char *av, t_env *env, int p_e)
{
	char	*str;
	int		env_len;

	env_len = find_dollar(av, env, p_e);
	if (env_len == -100)
	{
		free(av);
		return (NULL);
	}
	str = change_dollar(av, env, env_len, p_e);
	free(av);
	if (!str)
		return (NULL);
	return (str);
}
