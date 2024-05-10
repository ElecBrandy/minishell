/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:06:11 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/07 18:22:01 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../includes/minishell.h"

// /*
// 	heredoc 특징
// 	1. << "EOF" 형태만 가능
// 	2. 위 형태가 아닐경우 일단 heredoc이 실행되지만 상호작용하지 않음
// 	3. 위 형태가 아닐경우 실행종류 후 에러메세지 출력

// 	ex)
// 	<< aaa bbb : 일단 실행되지만 종료 후 "bash: bbb: command not found" 출력
// 	<< aaa bbb ccc : 일단 실행되지만 종료 후 "bash: bbb: command not found" 출력
// 	bbb << aaa ccc : 일단 실행되지만 종료 후 "bash: bbb: command not found" 출력
// 	<< aaa bbb > v.txt : 일단 실행되지만 종료 후 "bash: bbb: command not found" 출력 (v.txt 빈파일)
	
// 	ex2)
// 	cat << EOF : 실행 후 cat 실행
// 	cat cat << EOF : 실행 후 "cat: cat: No such file or directory 출력"
// */

// /*
// 	일단 << 가 존재할 경우 무조건 실행되는 듯 하니, 실행부분만 만들어보고 나중에 수정(5.7)
// 	현재 일단 입력 받은 다음에, 임시파일 만들고, 그 파일에 임시 저장
// */

// char	*here_doc(t_cmd *node)
// {
// 	int		out_fd;
// 	char	*line;
// 	char	*eof = "EOF\n"; // ft_strjoin으로 나중에 실제 eof와 \n 묶어주기

// 	// eof = ft_strjoin(node->cmd, "\n"); // 나중에 이거 주석 해제해야함!
// 	// if (!eof)
// 	// 	exit(1); // Error

// 	while (1)
// 	{
// 		line = readline("> ");
// 		if (!line || ft_strncmp(line, eof, ft_strlen(eof)) == 0)
// 		{
// 			ft_free((void **)&line);
// 			break ;
// 		}
// 	}
// }


// void process_here_doc(char *delimiter, char **extra_args) {
//     char *line;

//     printf("Start here-doc, type '%s' when done.\n", delimiter);
//     while (1) {
//         line = readline("> ");
//         if (line == NULL) {
//             fprintf(stderr, "Error or EOF encountered.\n");
//             break;
//         }

//         if (strcmp(line, delimiter) == 0) {
//             free(line);
//             break;
//         }

//         printf("Input: %s\n", line);
//         free(line);
//     }

//     // Here-doc 이후의 추가 인자 처리
//     if (*extra_args) {
//         fprintf(stderr, "bash: %s: command not found\n", *extra_args);
//         exit(EXIT_FAILURE);
//     }
// }
