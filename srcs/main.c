// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/18 17:36:26 by dongwook          #+#    #+#             */
// /*   Updated: 2024/05/18 18:31:54 by dongwook         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/minishell.h"

// static t_node *create_node_tmp(char **cmd, char *path, int in_fd, int out_fd);
// static char **copy_cmd(char **cmd);

// void	check_leak(void)
// {
// 	system("leaks minishell > log");
// }

// int main(int ac, char **av, char **envp)
// {
//     t_env *env;
//     t_node *node;

//     check_leak();
//     node = create_node_tmp(av, NULL, 0, 1);
//     env = env_array_to_list(env, envp);
//     // env 출력 검사
//     // print_env_list(env);
//     // ft_env(env, node);
//     printf("node->cmd[0] : %s\n", node->cmd[0]);
//     if (node->cmd[1] != NULL)
//         printf("node->cmd[1] : %s\n", node->cmd[1]);
//     else
//         printf("node->cmd[1] : NULL\n");
//     ft_export(env, node);
//     return (0);
// }

// static char **copy_cmd(char **cmd)
// {
//     if (!cmd) return NULL;

//     // cmd 배열의 크기 계산
//     int count = 0;
//     while (cmd[count]) {
//         count++;
//     }

//     // 새로운 배열 할당
//     char **new_cmd = malloc((count + 1) * sizeof(char*));
//     if (!new_cmd) return NULL;

//     // 각 문자열 복사
//     for (int i = 0; i < count; i++) {
//         new_cmd[i] = strdup(cmd[i]);
//         if (!new_cmd[i]) {  // 복사 실패 시 메모리 해제
//             for (int j = 0; j < i; j++) {
//                 free(new_cmd[j]);
//             }
//             free(new_cmd);
//             return NULL;
//         }
//     }
//     new_cmd[count] = NULL;  // 마지막은 NULL로 마무리
//     return new_cmd;
// }

// static t_node *create_node_tmp(char **cmd, char *path, int in_fd, int out_fd)
// {
//     t_node *new_node = malloc(sizeof(t_node));
//     if (new_node == NULL) {
//         return NULL;
//     }

//     new_node->cmd = copy_cmd(cmd);  // cmd 배열 복사
//     if (path) {
//         new_node->path = strdup(path);
//     } else {
//         new_node->path = NULL;
//     }
//     new_node->in_fd = in_fd;
//     new_node->out_fd = out_fd;
//     new_node->next = NULL;

//     // 초기화 중 에러 처리
//     if ((cmd && !new_node->cmd) || (path && !new_node->path)) {
//         free(new_node->cmd);  // cmd 메모리 해제
//         free(new_node->path); // path 메모리 해제
//         free(new_node);       // 구조체 메모리 해제
//         return NULL;
//     }

//     return new_node;
// }