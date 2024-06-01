/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_in_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:26:26 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/27 18:53:09 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_other(char *str, char *av, int *a_idx, int *s_idx)
{
	str[++(*s_idx)] = av[*a_idx];
	while (av[++(*a_idx)])
	{
		if (av[*a_idx] == 34)
			break ;
		str[++(*s_idx)] = av[*a_idx];
	}
	str[++(*s_idx)] = av[*a_idx];
}

static void	write_other_two(char *str, char *av, int *a_idx, int *s_idx)
{
	str[++(*s_idx)] = av[*a_idx];
	while (av[++(*a_idx)])
	{
		if (av[*a_idx] == 39)
			break ;
		str[++(*s_idx)] = av[*a_idx];
	}
	str[++(*s_idx)] = av[*a_idx];
}

static void	write_space(char *str, char *av, t_util *u)
{
	if ((u->i > 1)
		&& (av[u->i] == '<' || av[u->i] == '>')
		&& (av[u->i - 1] != '<' && av[u->i - 1] != '>' && av[u->i - 1] != ' '))
		str[++(u->idx)] = ' ';
	str[++(u->idx)] = av[u->i];
	if ((av[u->i] == '<' || av[u->i] == '>')
		&& (av[u->i + 1] != '<' && av[u->i + 1] != '>' && av[u->i + 1] != ' '))
		str[++(u->idx)] = ' ';
}

char	*add_space(char *av)
{
	t_util	u;
	char	*str;
	int		original_length;

	util_init(&u);
	original_length = ft_strlen(av);
	u.flag = get_flagcnt(av);
	str = malloc(sizeof(char) * (original_length + (u.flag * 2) + 1));
	if (!str)
		return (NULL);
	while (av[++u.i])
	{
		if (av[u.i] == 34)
			write_other(str, av, &u.i, &u.idx);
		else if (av[u.i] == 39)
			write_other_two(str, av, &u.i, &u.idx);
		else
			write_space(str, av, &u);
		if (av[u.i] == '\0')
			break ;
	}
	str[++u.idx] = '\0';
	return (str);
}

int	parsing_in_pipe(char *av, t_node *node, t_env *env, int p_e)
{
	t_util	u;
	char	*tmp;
	char	**str;
	char	**cmd;

	util_init(&u);
	tmp = add_space(av);
	if (!tmp)
		return (12);
	tmp = check_dollar(tmp, env, p_e);
	if (!tmp)
		return (12);
	u.cnt = find_flag(tmp, ' ') + find_flag(tmp, '\t');
	str = split_space(tmp, u.cnt);
	if (!str)
		return (12);
	cmd = find_fd(str, node, env, p_e);
	free_str(str);
	if ((!cmd) || g_signal_error)
		return (file_error());
	cmd = check_cmd(cmd);
	if (!cmd)
		return (12);
	g_signal_error = save_in_node(node, cmd);
	return (g_signal_error);
}
