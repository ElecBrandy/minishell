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

#include "../includes/minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
		printf("\033[Knimishell$ \n"); //있던 문자 지움
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 1);
	rl_redisplay();
}

void minishell(char *av, char **envp)
{
	t_node *head;
	t_node *node;
	char ***str;
	t_env env;
	t_util u;
	t_data *head_env;
	
	head = NULL;
	head_env = NULL;
	util_init(&u);
	str = parsing(av);

	/* ======= 환경변수 받아서 연결리스트로 변환하기 ====== */
	head_env = envp_to_linkedlist(head_env, envp);
	print_env_list(head_env); // 연결리스트 출력
	while (str[++u.i])
	{
		node = create_node(); // 새 노드 생성
		if (!node)
			exit (1); // Error
		append_node(&head, node); // 새 노드를 리스트에 추가
		u.j = -1;
		while (str[u.i][++u.j])
		{
			if (u.j > 0) {
				node = create_node(); // 추가 노드 생성
				if (!node)
					exit (1); // Error
				append_node(&head, node); // 추가 노드를 리스트에 추가
			}
			parsing_in_pipe(str[u.i][u.j], node); // 파이프라인 파싱
		}
		u.cnt = count_node(head); // 노드 수 세기
		fork_process(head_env, head, u.cnt); // 프로세스 실행
		// print_linked_list(head); // 노드 다 출력
		unlink(".heredoc_tmp");
		free_node(head); // 노드 메모리 해제
		head = NULL; // 헤드 초기화
	}
	free_str_three(str); // 파싱된 문자열 해제
	str = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char			*av;
	struct termios	term;

	if (argc != 1 && !argv && !envp)
		exit (1); // Error
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	signal(SIGINT, sig_handler);				// CTRL + c
	signal(SIGQUIT, SIG_IGN);					// CTRL + /
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
			minishell(av, envp);
			free(av);
		}
	}
	exit (0);
}

