/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_outfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:45:07 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/29 13:37:33 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	append_file(char **str, t_util *u, t_node *node, t_env *env);
static void	new_file(char **str, t_util *u, t_node *node, t_env *env);

void	is_outfd(char **str, t_util *u, t_node *node, t_env *env)
{
	if (ft_strlen(str[u->i]) > 2)
		syntax_error((str[u->i] + 2), node);
	else
	{
		if (!str[u->i + 1])
			syntax_error(NULL, node);
		else if (str[u->i + 1][0] == '<' || str[u->i + 1][0] == '>')
			syntax_error(str[u->i + 1], node);
		else if (ft_strlen(str[u->i]) == 1)
			new_file(str, u, node, env);
		else if (str[u->i][1] == '>' && ft_strlen(str[u->i]) == 2)
			append_file(str, u, node, env);
	}
}

static void	new_file(char **str, t_util *u, t_node *node, t_env *env)
{
	char	*file;
	char	*tmp;

	if (node->out_fd != 1)
		close(node->out_fd);
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
	node->out_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (node->out_fd == -1)
		notfile_error(file);
	free(file);
	(u->i) += 1;
}

static void	append_file(char **str, t_util *u, t_node *node, t_env *env)
{
	char	*file;
	char	*tmp;

	if (node->out_fd != 1)
		close(node->out_fd);
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
	node->out_fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (node->out_fd == -1)
		notfile_error(file);
	(u->i) += 1;
	free(file);
}

int	get_cmd(char **cmd, t_util *u, char **str)
{
	cmd[(u->flag)++] = ft_strdup(str[u->i]);
	if (!cmd[u->flag - 1])
	{
		free_str(cmd);
		return (1);
	}
	return (0);
}

char	**find_fd(char **str, t_node *node, t_env *env, int p_e)
{
	char	**cmd;
	t_util	u;

	util_init(&u);
	u.prev_errnum = p_e;
	u.cnt = count_str(str);
	cmd = malloc(sizeof(char *) * (u.cnt + 1));
	if (!cmd)
		return (NULL);
	while (str[++u.i])
	{
		if (ft_strncmp(str[u.i], "<", 1) == 0)
			is_infd(str, &u, node, env);
		else if (ft_strncmp(str[u.i], ">", 1) == 0)
			is_outfd(str, &u, node, env);
		else if (get_cmd(cmd, &u, str) == 1)
			return (NULL);
		if (g_signal_error)
			return (free_all(cmd, u.flag));
	}
	cmd[u.flag] = NULL;
	return (cmd);
}
