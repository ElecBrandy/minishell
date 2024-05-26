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
	char	*path;
	char	**cmd;
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
	if (ft_strchr(node->cmd[0], '/') != NULL)
	{
		path = node->cmd[0];
	}
	else
	{
		path = check_path(tmp, node->cmd[0]);
		if (!path)
		{
			fprintf(stderr, "path is NULL\n");
			exit(1); // Error
		}
	}
	if (execve(path, node->cmd, tmp) == -1)
	{
		exit(1); // Error
	}
}

/*
	check_path
	환경변수 PATH에 있는 경로를 찾아서 해당 명령어가 있는지 확인한다.
	만약 없다면 NULL을 반환한다.
*/
static char	*check_path(char **env, char *cmd)
{
	char *path;
	char **path_list;

	path_list = split_paths(env);
	if (!path_list)
		return (NULL);
	path = make_path(cmd, path_list);
	if (!path)
		return (NULL);
	return (path);
}

/*
	split_paths
	main에서 envp로 받아온 문자열 중 "PATH="로 시작하는 줄(문자열)을 찾는다.
	해당 문자열을 찾은 후, 해당 문자열을 ':'으로 분리해 반환한다.
*/
static char	**split_paths(char **env)
{
	int		i;
	char	**path_list;

	i = 0;
	if (env == NULL)
		return (NULL);
	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (!env[i])
		return (NULL); // PATH가 없는 경우
	path_list = ft_split(env[i] + 5, ':');
	if (!path_list)
		return (NULL);
	return (path_list);  // 분리된 경로 목록 반환
}

/*
	make_path
	':'로 분리되어 이중배열에 담긴 path_list / 명령어 cmd를 인자로 받는다.
	각각의 path_list와 cmd를 합쳐보면서 해당 명령어 주소가 유효한지 검사하다.
*/
static char	*make_path(char *cmd, char **path_list)
{
	size_t	i;
	char	*tmp;
	char	*path;

	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		// ft_free((void **)&tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		ft_free((void **)&path);
		i++;
	}
	return (NULL);
}
