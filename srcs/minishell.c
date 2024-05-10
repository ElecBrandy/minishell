/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:28:09 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/05 17:29:36 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"
#include "../libft/libft.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		printf("\033[Knimishell$ \n"); //있던 문자 지움
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void	minishell(char *av)
{
	t_node	*head;
	t_node	*node;
	char	***str;
	t_util	u;

	util_init(&u);
	str = parsing(av);
	while (str[++u.i])
	{
		head = make_node(head);
		node = head;
		while (str[u.i][++u.j])
		{
			if (u.j > 0)
				node = make_node(head);
			parsing_in_pipe(str[u.i][u.j], node);
		}
		//execve("/usr/bin/sed", head->cmd, NULL);
	 	//실행부
		// int q;
		// int k = 0;
		// t_node *abc;
		// abc = head;
		// while (abc)
		// {
		//  	q = -1;
		// 	printf("pipe line %d :--------\n", k++);
		// 	if (!abc->cmd)
		// 		printf("error\n");
		// 	else{
		// 		while (abc->cmd[++q])
		// 			printf("%s  ", abc->cmd[q]);
		// 		printf("\n");
		// 	}
		// 	abc = abc->next;
		// }
		unlink(".heredoc_tmp");
		free_node(head);
		head = NULL;
	}
	free_str_three(str);
	str = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char			*av;
	struct termios	term;

	if (argc == 0 && argv && envp)
		exit (0);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, sig_handler);// CTRL + c
	signal(SIGQUIT, SIG_IGN);// CTRL + /
	while (1)
	{
		av = readline("nimishell$ ");
		if (!av)
		{
			printf("\033[1A");
			printf("\033[10C");
			printf(" exit\n");
			exit (0);
		}
		else if (*av == '\0')
			free(av);
		else
		{
			add_history(av);
			minishell(av);
			free(av);
		}
	}
	exit (0);
}
