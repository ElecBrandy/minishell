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

int	find_dollar(char *av, char ***env)
{
	t_util	u;
	int		env_len;

	env_len = 0;
	util_init(&u);
	while (av[++u.i])
	{
		if (av[u.i] == '$' && av[u.i + 1] != ' '
			&& av[u.i + 1] != '\0' && av[u.i + 1] != 34
			&& av[u.i + 1] != 39)
			env_len += find_env(av, &u.i, env);
		else if (av[u.i] == 39)
			u.i = find_next_quote(av, u.i, 39);
	}
	return (env_len);
}

char	***make_env(t_env e)
{
	t_util	u;
	char	***env;

	util_init(&u);
	u.idx = count_str(e.arr);
	env = malloc(sizeof(char **) * (u.idx + 1));
	while (e.arr[++u.i])
		env[u.i] = ft_split(e.arr[u.i], '=');
	env[u.i] = NULL;
	return (env);
}

int	find_env(char *av, int *idx, char ***env)
{
	int		word_len;
	int		env_len;
	int		len;
	int		i;
	char	*word;

	i = -1;
	len = 0;
	word = get_word(av, idx);
	word_len = ft_strlen(word);
	while (env[++i])
	{
		env_len = ft_max(word_len, ft_strlen(env[i][0]));
		if (ft_strncmp(env[i][0], word, env_len) == 0)
			len = ft_strlen(env[i][1]) - word_len;
	}
	len--;
	free(word);
	return (len);
}
