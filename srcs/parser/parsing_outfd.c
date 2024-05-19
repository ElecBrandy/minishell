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
	if (!str[(*i) + 1])
		perror("no");
	else
	{
		if (str[(*i) + 1][0] == '<' || str[(*i) + 1][0] == '>')
		{
			perror("not file out");
			return ;
		}
		if (ft_strlen(str[*i]) == 1)
			new_file(str, i, node);
		else if (str[*i][1] == '>')
			append_file(str, i, node);
		else
		{
			if (node->out_fd != 1)
				close(node->out_fd);
			perror("notfile error");
		}
	}
}

void	new_file(char **str, int *i, t_node *node)
{
	char	*file;

	if (node->out_fd != 1)
		close(node->out_fd);
	file = del_quote(str[(*i) + 1]);
	node->out_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(file);
	*i += 1;
	if (node->out_fd == -1)
	{
		perror("makefile error");
		exit (1);
	}
}

void	append_file(char **str, int *i, t_node *node)
{
	char	*file;

	if (node->out_fd != 1)
		close(node->out_fd);
	file = del_quote(str[(*i) + 1]);
	node->out_fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	*i += 1;
	free(file);
	if (node->out_fd == -1)
	{
		perror("append file error");
		exit (1);
	}
}

char	**find_fd(char **str, t_node *node, t_env *env)
{
	char	**cmd;
	int		i;
	int		idx;

	idx = 0;
	i = -1;
	while (str[idx])
		idx++;
	cmd = malloc(sizeof(char *) * (idx + 1));
	idx = 0;
	while (str[++i])
	{
		if (ft_strncmp(str[i], "<", 1) == 0)
			is_infd(str, &i, node, env);
		else if (ft_strncmp(str[i], ">", 1) == 0)
			is_outfd(str, &i, node);
		else
			cmd[idx++] = ft_strdup(str[i]);
	}
	cmd[idx] = NULL;
	free_str(str);
	return (cmd);
}
