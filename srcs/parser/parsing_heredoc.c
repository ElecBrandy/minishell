/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:27:33 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/16 18:29:06 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*heredoc_check_dollar(char *av, t_env *env, t_node *node)
{
	char	*str;
	int		env_len;

	env_len = find_dollar(av, env, node->prev_errnum);
	str = change_dollar(av, env, env_len, node->prev_errnum);
	free(av);
	return (str);
}

int	heredoc_readline(char *av, char *limiter, t_node *node, t_env *env)
{
	add_history(av);
	if ((ft_strncmp(limiter, av, ft_strlen(limiter)) == 0)
		&& (ft_strlen(limiter) == ft_strlen(av)))
		return (1);
	av = heredoc_check_dollar(av, env, node);
	write(node->in_fd, av, ft_strlen(av));
	write(node->in_fd, "\n", 1);
	free(av);
	return (0);
}

void	heredoc_process(char **str, int *i, t_node *node, t_env *env)
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
			if (heredoc_readline(av, limiter, node, env) == 1)
				break ;
		}
		if (!str)
			break ;
	}
	free(limiter);
	free(av);
}

void	heredoc_infile(char **str, int *i, t_node *node, t_env *env)
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
	heredoc_process(str, i, node, env);
}
