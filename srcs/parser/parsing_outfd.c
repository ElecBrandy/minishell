/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_outfd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:45:07 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:45:09 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_outfd(char **str, int *i, t_node *node)
{
	if (ft_strlen(str[*i]) > 2)
		syntax_error((str[*i] + 2), node);
	else
	{
		if (!str[*i + 1])
			syntax_error(NULL, node); //newline
		else if (str[(*i) + 1][0] == '<' || str[(*i) + 1][0] == '>')
			syntax_error(str[*i + 1], node); // token < << > >>
		else if (ft_strlen(str[*i]) == 1)
			new_file(str, i, node);
		else if (str[*i][1] == '>' && ft_strlen(str[*i]) == 2)
			append_file(str, i, node);
	}
}

void	new_file(char **str, int *i, t_node *node)
{
	char	*file;

	if (node->out_fd != 1)
		close(node->out_fd);
	file = del_quote(str[(*i) + 1]);
	if (!file)
	{
		g_signal_error = 12;
		return ;
	}
	node->out_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (node->out_fd == -1)
	{
		printf("minishell: %s: %s\n", file, strerror(2));
		g_signal_error = 1;
	}
	free(file);
	*i += 1;
}

void	append_file(char **str, int *i, t_node *node)
{
	char	*file;

	if (node->out_fd != 1)
		close(node->out_fd);
	file = del_quote(str[(*i) + 1]);
	if (!file)
	{
		g_signal_error = 12;
		return ;
	}
	node->out_fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (node->out_fd == -1)
	{
		printf("minishell: %s: %s\n", file, strerror(2));
		g_signal_error = 1;
	}
	*i += 1;
	free(file);
}

int	get_cmd(char **cmd, t_util *u, char **str)
{
	cmd[(u->flag)++] = ft_strdup(str[u->i]);
	if (!cmd[u->flag])
	{
		free_str(str);
		free_str(cmd);
		return (1);
	}
	return (0);
}

char	**find_fd(char **str, t_node *node, t_env *env)
{
	char	**cmd;
	t_util	u;

	util_init(&u);
	u.cnt = count_str(str);
	cmd = malloc(sizeof(char *) * (u.cnt + 1));
	if (!cmd)
	{
		free_str(str);
		return (NULL);
	}
	while (str[++u.i])
	{
		if (ft_strncmp(str[u.i], "<", 1) == 0)
			is_infd(str, &(u.i), node, env);
		else if (ft_strncmp(str[u.i], ">", 1) == 0)
			is_outfd(str, &(u.i), node);
		else if (get_cmd(cmd, &u, str))
			return (NULL);
		if (g_signal_error)
			return (NULL);
	}
	cmd[u.flag] = NULL;
	free_str(str);
	return (cmd);
}
