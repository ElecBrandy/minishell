/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:28:09 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/19 17:53:31 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parsing_minishell(t_node **head, char **str, t_env *env, int p_e)
{
	t_node	*node;
	t_util	u;

	util_init(&u);
	node = create_node(p_e);
	if (!node)
		return (12);
	append_node(head, node);
	u.j = -1;
	while (str[++u.j])
	{
		if (u.j > 0)
		{
			node = create_node(p_e);
			if (!node)
				return (12);
			append_node(head, node);
		}
		u.cnt = parsing_in_pipe(str[u.j], node, env, p_e);
		if (u.cnt)
			break ;
	}
	return (u.cnt);
}

int	parsing_check_errno(t_node **head, char **str, t_env *env, int p_e)
{
	if (parsing_minishell(head, str, env, p_e))
		return (1);
	return (0);
}

int	minishell(char *av, t_env **env, char *home)
{
	t_node	*head;
	char	***str;
	t_util	u;

	str = parsing(av);
	if (!str)
		return (print_error());
	util_init(&u);
	while (str[++u.i])
	{
		if (str[u.i][0][0] != 0)
		{
			u.prev_errnum = g_signal_error;
			g_signal_error = 0;
			head = NULL;
			if (parsing_check_errno(&head, str[u.i], *env, u.prev_errnum))
				print_error();
			else
				processing(env, head, home);
			free_node(head);
		}
	}
	free_str_three(str);
	return (0);
}

void	readline_minishell(t_env **env, char *home)
{
	char	*av;

	while (1)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		av = readline("minishell$ ");
		if (!av)
		{
			printf("exit\n");
			exit (g_signal_error);
		}
		else if (*av == '\0')
			free(av);
		else
		{
			add_history(av);
			minishell(av, env, home);
			free(av);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_env			*env;
	char			*home;

	if (argc != 1 || !argv || !envp)
		exit (1);
	env = NULL;
	set_home(envp, &home);
	set_env_list(&env, envp);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	readline_minishell(&env, home);
	exit (g_signal_error);
}
