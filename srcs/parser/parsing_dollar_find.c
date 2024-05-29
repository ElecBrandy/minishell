/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_find.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:40:51 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:47:34 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_print(char s)
{
	int	flag;

	flag = 0;
	if ((s >= '0' && s <= '9') || (s >= 'A' && s <= 'Z')
		|| (s >= 'a' && s <= 'z') || s == '_')
		flag = 1;
	return (flag);
}

void	jump_next_word(char *av, t_util *u)
{
	u->flag = 0;
	while (av[++u->i])
	{
		if (av[u->i] != ' ' || av[u->i] != '<' || av[u->i] != '>')
			break ;
	}
	if (av[u->i] == '\0')
		return ;
	while (av[++u->i])
	{
		if (av[u->i] == ' ')
			break ;
	}
}

int	find_dollar_two(char *av, t_env *env, int p_e, t_util *u)
{
	if (av[u->i] == '$' && is_print(av[u->i + 1]))
	{
		u->idx = find_env(av, &u->i, env);
		if (u->idx == -100)
			return (-100);
		u->cnt += u->idx;
	}
	else if (av[u->i] == 34)
	{
		if (in_doublequote(av, p_e, env, u))
			return (-100);
	}
	else if (av[u->i] == 39)
		u->i = find_next_quote(av, u->i, 39);
	return (0);
}

int	find_dollar(char *av, t_env *env, int p_e)
{
	t_util	u;

	util_init(&u);
	while (av[++u.i])
	{
		if (av[u.i] == '<' || av[u.i] == '>')
			u.flag = 1;
		if (u.flag == 1)
			jump_next_word(av, &u);
		else
		{
			if (av[u.i] == '$' && av[u.i + 1] == '?')
				u.cnt += (get_numlen(p_e) - 2);
			else if (find_dollar_two(av, env, p_e, &u))
				return (-100);
		}
		if (av[u.i] == '\0')
			break ;
	}
	return (u.cnt);
}

char	*get_word(char *av, int *idx)
{
	t_util	u;
	char	*word;

	util_init(&u);
	u.i = (*idx);
	while (av[++u.i])
	{
		if (is_print(av[u.i]))
			u.cnt++;
		else
			break ;
	}
	word = malloc(sizeof(char) * (u.cnt + 1));
	if (!word)
		return (malloc_fail());
	put_word(av, word, idx);
	(*idx)--;
	return (word);
}
