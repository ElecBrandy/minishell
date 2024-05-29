/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_put.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:43:03 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:43:04 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	put_change_dollar(char *av, char *str, t_env *env, t_util *u)
{
	if (av[u->i] == 34)
		putin_doublequote(av, str, env, u);
	else if (av[u->i] == '$' && av[u->i + 1] == '?')
		put_errno(str, u->prev_errnum, u);
	else if (av[u->i] == 39)
		put_str(str, av, &u->i, &u->idx);
	else if (av[u->i] == '$' && is_print(av[u->i + 1]))
		put_env(str, av, env, u);
	else
		str[++(u->idx)] = av[u->i];
}

void	put_word(char *av, char *word, int *idx)
{
	int	i;

	i = -1;
	while (av[++(*idx)])
	{
		if (is_print(av[*idx]))
			word[++i] = av[*idx];
		else
			break ;
	}
	word[++i] = '\0';
}

void	put_str(char *str, char *av, int *a_idx, int *s_idx)
{
	str[++(*s_idx)] = av[*a_idx];
	while (av[++(*a_idx)] != 39)
		str[++(*s_idx)] = av[*a_idx];
	str[++(*s_idx)] = av[*a_idx];
}

void	put_env(char *str, char *av, t_env *env, t_util *u)
{
	char	*word;
	int		env_len;
	int		idx;
	t_env	*e;

	e = env;
	word = get_word(av, &u->i);
	if (!word)
		return ;
	u->j = -1;
	while (e)
	{
		env_len = ft_max(ft_strlen(word), ft_strlen(e->key));
		if (ft_strncmp(e->key, word, env_len) == 0)
		{
			idx = -1;
			while (e->value[++idx])
				str[++(u->idx)] = e->value[idx];
			break ;
		}
		e = e->next;
	}
	free(word);
}
