/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_dollar_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:14:10 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/16 19:14:11 by dongeunk         ###   ########.fr       */
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

int	find_dollar(char *av, t_env *env, int p_e)
{
	t_util	u;
	int		env_len;

	env_len = 0;
	util_init(&u);
	while (av[++u.i])
	{
		if (av[u.i] == '$' && av[u.i + 1] == '?')
			env_len = (get_numlen(p_e) - 2);
		else if (av[u.i] == '$' && is_print(av[u.i + 1]))
			env_len += find_env(av, &u.i, env);
		else if (av[u.i] == 39)
			u.i = find_next_quote(av, u.i, 39);
	}
	return (env_len);
}

int	find_env(char *av, int *idx, t_env *env)
{
	int		word_len;
	int		env_len;
	int		len;
	int		i;
	char	*word;
	t_env	*e;

	e = env;
	i = -1;
	len = 0;
	word = get_word(av, idx);
	word_len = ft_strlen(word);
	while (e)
	{
		env_len = ft_max(word_len, ft_strlen(e->key));
		if (ft_strncmp(e->key, word, env_len) == 0)
		{	
			len = ft_strlen(e->value) - word_len;
			len--;
			break ;
		}
		e = e->next;
	}
	free(word);
	return (len);
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
