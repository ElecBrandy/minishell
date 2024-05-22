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

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		//printf("sigint\n");
		printf("\n"); //있던 문자 지움
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int	parsing_minishell(t_node **head, char **str, t_env *env, t_errnum *e)
{
	t_node	*node;
	t_util	u;

	util_init(&u);
	node = create_node(e->prev_errnum); // 새 노드 생성
	if (!node)
		return (12);
	append_node(head, node); // 새 노드를 리스트에 추가
	u.j = -1;
	while (str[++u.j])
	{
		if (u.j > 0)
		{
			node = create_node(e->prev_errnum); // 추가 노드 생성
			if (!node)
				return (12); // Error
			append_node(head, node); // 추가 노드를 리스트에 추가
		}
		u.cnt = parsing_in_pipe(str[u.j], node, env, e);
		if (u.cnt)
			break ;
	}
	return (u.cnt);
}

void	minishell(char *av, t_env *env, t_errnum *e)
{
	t_node	*head;
	char	***str;
	t_util	u;

	util_init(&u);
	e->prev_errnum = e->errnum;
	e->errnum = 0;
	str = parsing(av); // str[세미콜론][파이프][파이프 내부]로 파싱
	if (!str)
	{
		print_error();
		return ;
	}
	while (str[++u.i])
	{
		head = NULL;
		if (parsing_minishell(&head, str[u.i], env, e))
		{
			if (head)
				free_node(head);
			print_error();
			break ;
		}
		u.cnt = count_node(head); // 노드 수 세기
		fork_process(env, head, u.cnt); // 프로세스 실행
	//	print_linked_list(head); // 노드 다 출력
		free_node(head); // 노드 메모리 해제
	}
	free_str_three(str); // 파싱된 문자열 해제
}

void	readline_minishell(t_env *env, t_errnum *e)
{
	char	*av;

	while (1)
	{
		av = readline("nimishell$ ");
		if (!av)
		{
			printf("exit\n");
			exit (0);
		}
		else if (*av == '\0')
			free(av);
		else
		{
			add_history(av);
			minishell(av, env, e);
			free(av);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_env			*env;
	t_errnum		e;

	e.errnum = 0;
	e.prev_errnum = 0;
	if (argc != 1 || !argv || !envp)
	{
		g_errnum = 3;
		printf("%s\n", strerror(g_errnum));
		exit (g_errnum);
	}
	env = env_array_to_list(env, envp); // 연결리스트로 만들기
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, sig_handler);// CTRL + c
	signal(SIGQUIT, SIG_IGN);// CTRL + |
	readline_minishell(env, &e);
	exit (g_errnum);
}
