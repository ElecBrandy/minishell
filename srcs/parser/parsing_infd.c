/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_infd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:43:57 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:44:07 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	only_open(char **str, int *i);
static void	check_infile(char **str, int *i, t_node *node);

static void	check_infile(char **str, int *i, t_node *node)
{
	char	*file;

	if (node->in_fd != 0)
		close(node->in_fd);
	file = del_quote(str[(*i) + 1]);
	if (!file)
	{
		g_signal_error = 12;
		return ;
	}
	node->in_fd = open(file, O_RDONLY);
	if (node->in_fd == -1) // No such file or directory
	{
		printf("minishell: %s: %s\n", file, strerror(2));
		g_signal_error = 999;
	}
	*i += 1;
	free(file);
}

static void	only_open(char **str, int *i)
{
	char	*file;
	int		fd;

	file = del_quote(str[(*i) + 1]);
	if (!file)
	{
		g_signal_error = 12;
		return ;
	}
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1) // No such file or directory
	{
		printf("minishell: %s: %s\n", file, strerror(2));
		g_signal_error = 999;
	}
	close(fd);
	free(file);
	*i += 1;
}

void	is_infd(char **str, int *i, t_node *node, t_env *env)
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
			check_infile(str, i, node);
		else if (ft_strncmp(str[*i], "<<", ft_strlen(str[*i])) == 0)
			heredoc_infile(str, i, node, env);
		else if (str[*i][1] == '>' && ft_strlen(str[*i]) == 2)
			only_open(str, i);
	}
}
