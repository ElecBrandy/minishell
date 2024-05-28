/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:43:57 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/27 18:52:23 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	only_open(char **str, t_util *u, t_env *env);
static void	check_infile(char **str, t_util *u, t_node *node, t_env *env);

int	check_file(char *str)
{
	t_util	u;

	util_init(&u);
	if (str[0] == 0)
		return (1);
	while (str[++u.i])
	{
		if (str[u.i] == 34)
			u.i = find_next_quote(str, u.i, 34);
		else if (str[u.i] == 39)
			u.i = find_next_quote(str, u.i, 39);
		else
		{
			if (check_file_two(str, &u))
				return (1);
		}
		if (!str[u.i])
			break ;
	}
	return (0);
}

char	*file_check_dollar(char *av, t_env *env, int p_e)
{
	char	*tmp;
	int		env_len;

	env_len = find_dollar(av, env, p_e);
	if (env_len == -100)
	{
		return (NULL);
	}
	tmp = change_dollar(av, env, env_len, p_e);
	if (!tmp)
		return (NULL);
	tmp = ft_strtrim(tmp, " \t");
	return (tmp);
}

static void	check_infile(char **str, t_util *u, t_node *node, t_env *env)
{
	char	*file;
	char	*tmp;

	if (node->in_fd != 0)
		close(node->in_fd);
	tmp = file_check_dollar(str[u->i + 1], env, u->prev_errnum);
	if (check_file(tmp))
	{
		printf("minishell: %s: ambiguous redirect\n", str[u->i + 1]);
		free(tmp);
		g_signal_error = 999;
		return ;
	}
	file = del_quote(tmp);
	free(tmp);
	if (!file)
	{
		g_signal_error = 12;
		return ;
	}
	node->in_fd = open(file, O_RDONLY);
	if (node->in_fd == -1)
		notfile_error(file);
	(u->i) += 1;
	free(file);
}

static void	only_open(char **str, t_util *u, t_env *env)
{
	char	*file;
	char	*tmp;
	int		fd;

	tmp = file_check_dollar(str[u->i + 1], env, u->prev_errnum);
	if (check_file(tmp))
	{
		printf("minishell: %s: ambiguous redirect\n", str[u->i + 1]);
		g_signal_error = 999;
		free(tmp);
		return ;
	}
	file = del_quote(tmp);
	free(tmp);
	if (!file)
	{
		g_signal_error = 12;
		return ;
	}
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		notfile_error(file);
	close(fd);
	free(file);
	u->i += 1;
}

void	is_infd(char **str, t_util *u, t_node *node, t_env *env)
{
	if (ft_strlen(str[u->i]) > 2)
		syntax_error((str[u->i] + 2), node);
	else
	{
		if (!str[u->i + 1])
			syntax_error(NULL, node);
		else if (str[(u->i) + 1][0] == '<' || str[(u->i) + 1][0] == '>')
			syntax_error(str[u->i + 1], node);
		else if (ft_strlen(str[u->i]) == 1)
			check_infile(str, u, node, env);
		else if (ft_strncmp(str[u->i], "<<", ft_strlen(str[u->i])) == 0)
			heredoc_infile(str, &(u->i), node, env);
		else if (str[u->i][1] == '>' && ft_strlen(str[u->i]) == 2)
			only_open(str, u, env);
	}
}
