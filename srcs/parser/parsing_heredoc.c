/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:27:33 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:43:40 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc_check_dollar(char *av, t_env *env, t_node *node)
{
	char	*str;
	int		env_len;

	env_len = heredoc_find_dollar(av, env, node->prev_errnum);
	if (env_len == -100)
	{
		free(av);
		return (NULL);
	}
	str = heredoc_change_dollar(av, env, env_len, node->prev_errnum);
	free(av);
	if (!str)
		return (NULL);
	return (str);
}

int	heredoc_readline(char *av, char *str, t_node *node, t_env *env)
{
	char	*limiter;
	int		flag;

	flag = 0;
	if (ft_strchr(str, 34) || ft_strchr(str, 39))
		limiter = del_quote(str);
	else
	{
		limiter = ft_strdup(str);
		flag = 1;
	}
	if (!limiter)
		return (12);
	if ((ft_strncmp(limiter, av, ft_strlen(limiter)) == 0)
		&& (ft_strlen(limiter) == ft_strlen(av)))
		return (1);
	free(limiter);
	if (flag == 1)
		av = heredoc_check_dollar(av, env, node);
	if (!av)
		return (12);
	write(node->in_fd, av, ft_strlen(av));
	write(node->in_fd, "\n", 1);
	free(av);
	return (0);
}

void	heredoc_process(char **str, int *i, t_node *node, t_env *env)
{
	char	*av;

	signal(SIGINT, heredoc_handler);
	while (1)
	{
		av = readline("> ");
		if (!av)
			break ;
		else if (*av == '\0')
			free(av);
		else
		{
			add_history(av);
			if (heredoc_readline(av, str[(*i)], node, env))
				break ;
		}
	}
	exit (g_signal_error);
}

void	heredoc_infile(char **str, int *i, t_node *node, t_env *env)
{
	pid_t			pid;
	int				status;

	unlink(".heredoc_tmp");
	if (node->in_fd != 0)
		close(node->in_fd);
	node->in_fd = open(".heredoc_tmp", O_RDWR | O_CREAT | O_APPEND, 0666);
	if (node->in_fd == -1)
	{
		printf("minishell: .heredoc_tmp: %s\n", strerror(2));
		g_signal_error = 1;
		return ;
	}
	*i += 1;
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		heredoc_process(str, i, node, env);
	wait(&status);
	g_signal_error = WEXITSTATUS(status);
	close(node->in_fd);
	node->in_fd = open(".heredoc_tmp", O_RDONLY);
	signal(SIGINT, sig_handler);
}
