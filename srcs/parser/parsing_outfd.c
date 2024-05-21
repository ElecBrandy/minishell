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
			is_infd(str, &u.i, node, env);
		else if (ft_strncmp(str[u.i], ">", 1) == 0)
			is_outfd(str, &u.i, node);
		else
			cmd[u.flag++] = ft_strdup(str[u.i]);
		if (!cmd[u.flag])
		{
			free_str(str);
			free_str(cmd);
			return (NULL);
		}
	}
	cmd[u.flag] = NULL;
	free_str(str);
	return (cmd);
}
