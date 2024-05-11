/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/12 01:22:36 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exec_cmd(t_env *env, t_node *node);
static char	*check_path(t_env *env, char *cmd);
static char	**split_paths(t_env *env);
static char	*make_path(char *cmd, char **path_list);

/*
	node 하나 잘라와서 (파이프 기준)
	명령어 실행
	run_cmd(env_head, node);
*/

int run_cmd(t_env *env, t_node *node)
{
	if (is_builtin(node) != 0) // builtin 일 경우
	{
		exec_builtin(env, node);
	}
	else // builtin 아니라 일반 함수인 경우
	{
		exec_cmd(env, node);
	}
	return (0);
}

// cmd 실행
static void exec_cmd(t_env *env, t_node *node)
{
	char	*path;
	char	**cmd;


	if (!env->arr)
	{
		exit(1); // Error
	}
	path = check_path(env, node->cmd[0]);
	if (!path)
	{
		exit(1); // Error
	}
	if (execve(path, node->cmd, env->arr) == -1)
	{
		exit(1); // Error
	}
}

/*
	check_path
	환경변수 PATH에 있는 경로를 찾아서 해당 명령어가 있는지 확인한다.
	만약 없다면 NULL을 반환한다.
*/
static char	*check_path(t_env *env, char *cmd)
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
static char	**split_paths(t_env *env)
{
	int		i;
	char	**path_list;

	i = 0;
	if (env->arr[i] == NULL)
		return (NULL);
	while (env->arr[i] && ft_strncmp("PATH=", env->arr[i], 5) != 0)
		i++;
	path_list = ft_split(env->arr[i] + 5, ':');
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
	if (access(cmd, X_OK) == 0) // 만약 실행 파일이 지정위치에 존재할경우
		return (cmd);
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd);
		ft_free((void **)&tmp);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
			return (path);
		ft_free((void **)&path);
		i++;
	}
	return (NULL);
}
