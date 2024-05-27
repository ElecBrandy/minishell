/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/26 20:42:15 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exec_cmd(t_env *head_env, t_node *node);
static char	*check_path(char **env, char *cmd);
static char	**split_paths(char **env);
static char	*make_path(char *cmd, char **path_list);


int run_cmd(t_env *head_env, t_node *node, char *home, pid_t pid)
{
	t_env *cur;

	if (is_builtin(node) != 0) // builtin 일 경우
	{
		exec_builtin(head_env, node, home, pid);
		exit(1); // Error? : 정상종료
	}
	else // builtin 아니라 일반 함수인 경우
	{
		// cur = is_env(head_env, "PATH");
		// if (cur->value[0] == '\0')
		// {
		// 	ft_putstr_fd("minishell: ", 2);
		// 	ft_putstr_fd(node->cmd[0], 2);
		// 	ft_putstr_fd(": No such file or directory\n", 2);
		// 	exit(1); // Error
		// }
		exec_cmd(head_env, node); // 환경변수단에 넣어보고 일단 실행
	}
	return (0);
}

// cmd 실행
static void exec_cmd(t_env *head_env, t_node *node)
{
	char 	**tmp;

	if (!head_env)
	{
		fprintf(stderr, "env is NULL\n");
		exit(1); // Error
	}
	tmp = env_list_to_array(head_env);
	if (!tmp)
	{
		fprintf(stderr, "env is NULL\n");
		exit(1); // Error
	}
	if (execve(node->path, node->cmd, tmp) == -1)
	{
		exit(1); // Error
	}
}
