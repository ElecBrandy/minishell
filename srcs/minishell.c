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
	node = create_node(p_e); // 새 노드 생성
	if (!node)
		return (12);
	append_node(head, node); // 새 노드를 리스트에 추가
	u.j = -1;
	while (str[++u.j])
	{
		if (u.j > 0)
		{
			node = create_node(p_e); // 추가 노드 생성
			if (!node)
				return (12); // Error
			append_node(head, node); // 추가 노드를 리스트에 추가
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
	{
		free_node(*head);
		return (1);
	}
	return (0);
}

int	minishell(char *av, t_env *env)
{
	t_node	*head;
	char	***str;
	t_util	u;

	util_init(&u);
	g_signal_error = 0;
	str = parsing(av); // str[세미콜론][파이프][파이프 내부]로 파싱
	if (!str)
		return (print_error());
	while (str[++u.i])
	{
		head = NULL;
		if (parsing_check_errno(&head, str[u.i], env, u.prev_errnum))
		{
			free_str_three(str); // 파싱된 문자열 해제
			return (print_error()); // error print
		}
		u.cnt = count_node(head); // 노드 수 세기
		signal(SIGINT, child_handler);// CTRL + c
		signal(SIGQUIT, child_handler);// CTRL + |
		fork_process(env, head, u.cnt); // 프로세스 실행
	//	print_linked_list(head); // 노드 다 출력
		free_node(head); // 노드 메모리 해제
	}
	free_str_three(str); // 파싱된 문자열 해제
	return (0);
}

void	readline_minishell(t_env *env)
{
	char	*av;

	while (1)
	{
		signal(SIGINT, sig_handler);// CTRL + c
		signal(SIGQUIT, SIG_IGN);// CTRL + |
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
			minishell(av, env);
			free(av);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	struct termios	term;
	t_env			*env;

	if (argc != 1 || !argv || !envp)
	{
		printf("%s\n", strerror(3));
		exit (3);
	}
	env = env_array_to_list(env, envp); // 연결리스트로 만들기
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	readline_minishell(env);
	exit (g_signal_error);
}
