/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:44:40 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:44:41 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	putin_doublequote(char *av, char *str, t_env *env, t_util *u)
{
	str[++u->idx] = '"';
	while (av[++u->i])
	{
		if (av[u->i] == '$' && av[u->i + 1] == '?')
			put_errno(str, av, u->flag, u);
		else if (av[u->i] == '$' && is_print(av[u->i + 1]))
			put_env(str, av, env, u);
		else
			str[++(u->idx)] = av[u->i];
	}
}

char	*heredoc_change_dollar(char *av, t_env *env, int env_len, int p_e)
{
	t_util	u;
	char	*str;
	char	*word;

	util_init(&u);
	u.cnt = ft_strlen(av);
	u.flag = p_e;
	str = malloc(sizeof(char) * (u.cnt + env_len + 1));
	while (av[++u.i])
	{
		if (av[u.i] == 34)
			putin_doublequote(av, str, env, &u);
		else if (av[u.i] == '$' && av[u.i + 1] == '?')
			put_errno(str, av, p_e, &u);
		else if (av[u.i] == 39)
			put_str(str, av, &u.i, &u.idx);
		else if (av[u.i] == '$' && is_print(av[u.i + 1]))
			put_env(str, av, env, &u);
		else
			str[++u.idx] = av[u.i];
		if (av[u.i] == '\0')
			break ;
	}
	str[++u.idx] = '\0';
	return (str);
}

void	in_doublequote(char *av, int p_e, t_env *env, t_util *u)
{
	while (av[++u->i])
	{
		if (av[u->i] == 34)
			break ;
		if (av[u->i] == '$' && av[u->i + 1] == '?')
			u->cnt += (get_numlen(p_e) - 2);
		else if (av[u->i] == '$' && is_print(av[u->i + 1]))
			u->cnt += find_env(av, &u->i, env);
	}
}

int	heredoc_find_dollar(char *av, t_env *env, int p_e)
{
	t_util	u;

	util_init(&u);
	while (av[++u.i])
	{
		if (av[u.i] == '$' && av[u.i + 1] == '?')
			u.cnt += (get_numlen(p_e) - 2);
		else if (av[u.i] == '$' && is_print(av[u.i + 1]))
			u.cnt += find_env(av, &u.i, env);
		else if (av[u.i] == 34)
			in_doublequote(av, p_e, env, &u);
		else if (av[u.i] == 39)
			u.i = find_next_quote(av, u.i, 39);
	}
	return (u.cnt);
}
