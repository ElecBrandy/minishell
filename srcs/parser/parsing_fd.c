/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:10:14 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/10 09:10:15 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	{
		perror("infile error");
		exit (1);
	}
}

void	heredoc_process(char **str, int *i, t_node *node)
{
	char	*av;
	char	*limiter;

	limiter = del_quote(str[(*i)]);
	while (1)
	{
		av = readline("> ");
		if (!av)
		{
			free(av);
			break ;
		}
		else if (*av == '\0')
			free(av);
		else
		{
			add_history(av);
			if ((ft_strncmp(limiter, av, ft_strlen(limiter)) == 0)
				&& (ft_strlen(limiter) == ft_strlen(av)))
				break ;
			write(node->in_fd, av, ft_strlen(av));
			write(node->in_fd, "\n", 1);
			free(av);
		}
		if (!str)
			break ;
	}
	free(limiter);
	free(av);
}

void	heredoc_infile(char **str, int *i, t_node *node)
{
	struct termios	ter;

	tcgetattr(STDIN_FILENO, &ter);
	ter.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &ter);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	unlink(".heredoc_tmp");
	if (node->in_fd != 0)
		close(node->in_fd);
	node->in_fd = open(".heredoc_tmp", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (node->in_fd == -1)
	{
		perror("minishell");
		exit (1);
	}
	*i += 1;
	heredoc_process(str, i, node);
}
