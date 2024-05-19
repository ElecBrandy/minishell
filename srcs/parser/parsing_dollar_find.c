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
	while (av[++u->i])
	{
		if (av[u->i] != ' ')
			break ;
	}
	while (av[++u->i])
	{
		if (av[u->i] == ' ')
			break ;
	}
	u->flag = 0;
}

int	find_dollar(char *av, t_env *env, int p_e)
{
	t_util	u;

	util_init(&u);
	while (av[++u.i])
	{
		if (u.i > 0 && (av[u.i] == '<' && av[u.i - 1] == '<'))
			u.flag = 1;
		if (u.flag == 1)
			jump_next_word(av, &u);
		else
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
		if (av[u.i] == '\0')
			break ;
	}
	return (u.cnt);
}

int	find_env(char *av, int *idx, t_env *env)
{
	int		word_len;
	int		env_len;
	t_util	u;
	char	*word;
	t_env	*e;

	util_init(&u);
	e = env;
	word = get_word(av, idx);
	word_len = ft_strlen(word);
	while (e)
	{
		env_len = ft_max(word_len, ft_strlen(e->key));
		if (ft_strncmp(e->key, word, env_len) == 0)
		{	
			u.cnt = ft_strlen(e->value) - word_len;
			u.cnt--;
			break ;
		}
		e = e->next;
	}
	free(word);
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
		exit (1); // error
	put_word(av, word, idx);
	(*idx)--;
	return (word);
}
