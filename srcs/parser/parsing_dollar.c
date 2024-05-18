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

void	put_word(char *av, char *word, int *idx)
{
	int	i;

	i = -1;
	while (av[++(*idx)])
	{
		if (av[*idx] != ' ' && av[*idx] != 34
			&& av[*idx] != 39 && av[*idx] != '$')
			word[++i] = av[*idx];
		else
			break ;
	}
	word[++i] = '\0';
}

char	*get_word(char *av, int *idx)
{
	t_util	u;
	char	*word;

	util_init(&u);
	u.i = (*idx);
	while (av[++u.i])
	{
		if (av[u.i] != ' ' && av[u.i] != 34 && av[u.i] != 39 && av[u.i] != '$')
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

char	*change_dollar(char *av, t_env *env, int env_len)
{
	int		len;
	int		idx;
	t_util	u;
	char	*str;
	char	*word;

	util_init(&u);
	len = ft_strlen(av);
	str = malloc(sizeof(char) * (len + env_len + 1));
	while (av[++u.i])
	{
		if (av[u.i] == 39)
			put_str(str, av, &u.i, &u.idx);
		else if (av[u.i] == '$' && av[u.i + 1] != ' '
			&& av[u.i + 1] != '\0' && av[u.i + 1] != 34 && av[u.i + 1] != 39)
		{
			put_env(str, av, env, &u);
		}
		else
			str[++u.idx] = av[u.i];
	}
	str[++u.idx] = '\0';
	return (str);
}

char	**check_dollar(char **av, t_env *env)
{
	char	**str;
	int		env_len;
	t_util	u;

	util_init(&u);
	u.cnt = count_str(av);
	str = malloc(sizeof(char *) * (u.cnt + 1));
	while (av[++u.i])
	{
		if (u.i > 0
			&& ft_strncmp(av[u.i - 1], "<<", ft_strlen(av[u.i - 1])) == 0)
			str[u.i] = ft_strdup(av[u.i]);
		else
		{
			env_len = find_dollar(av[u.i], env);
			str[u.i] = change_dollar(av[u.i], env, env_len);
		}
	}
	str[u.i] = NULL;
	return (str);
}
