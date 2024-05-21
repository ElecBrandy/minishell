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

void	check_infile(char **str, int *i, t_node *node)
{
	char	*file;

	if (node->in_fd != 0)
		close(node->in_fd);
	file = del_quote(str[(*i) + 1]);
	node->in_fd = open(file, O_RDONLY);
	*i += 1;
	free(file);
	if (node->in_fd == -1)
		perror("infile error");
}

void	only_open(char **str, int *i)
{
	char	*file;
	int		fd;

	file = del_quote(str[(*i) + 1]);
	fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	close(fd);
	free(file);
	*i += 1;
}

void	is_infd(char **str, int *i, t_node *node, t_env *env)
{
	if (!str[(*i) + 1])
		g_errnum = 258;
	else
	{
		if (str[(*i) + 1][0] == '<' || str[(*i) + 1][0] == '>')
		{
			g_errnum = 258;
			return ;
		}
		if (ft_strlen(str[*i]) == 1)
			check_infile(str, i, node);
		else if (ft_strncmp(str[*i], "<<", ft_strlen(str[*i])) == 0)
			heredoc_infile(str, i, node, env);
		else if (str[*i][1] == '>')
			only_open(str, i);
		else
		{
			perror("notfile error2");
		}
	}
}
