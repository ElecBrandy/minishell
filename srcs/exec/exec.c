/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 16:33:05 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void exec_cmd(t_env *env_head, t_cmd *node);
static char	*check_path(t_env *env_head, char *cmd);
static char	**split_paths(t_env *env_head);
static char	*make_path(char *cmd, char **path_list);

/* 
	node 하나 잘라와서 (파이프 기준)
	명령어 실행
	run_cmd(env_head, node);
*/
int run_cmd(t_env *env_head, t_cmd *node)
{
	if (is_redirection(node) == 0) // redritection 존재하는 경우
	{
		printf("redirection\n");
		return (0); // 일단 보류
	}
	else // redriection 존재하지 않는 경우
	{
		if (is_builtin(node) != 0) // builtin 일 경우
		{
			exec_builtin(env_head, node);
		}
		else // builtin 아니라 일반 함수인 경우
		{
			exec_cmd(env_head, node);
		}
	}
	return (0);
}

// cmd 실행
static void exec_cmd(t_env *env_head, t_cmd *node)
{
	char	*path;
	char	**cmd;
	char	**envp;

	envp = env_to_char(env_head);
	if (!envp)
	{
		exit(1); // Error
	}
	path = check_path(env_head, node->cmd[0]);
	if (!path)
	{
		exit(1); // Error
	}
	if (execve(path, node->cmd, envp) == -1)
	{
		perror("Minishell");
		exit(1); // Error
	}
}

/*
	env_to_char
	환경변수 연결리스트를 받아와서 char **로 변환한다.
	환경변수 연결리스트의 각 노드의 line을 char *로 변환한다.
	관리는 연결리스트로 하지만, execve에 줄때는 어처피 char **로 줘야하기 때문에 변환한다.
*/

char	**env_to_char(t_env *env_head)
{
	size_t	i;
	t_env	*cur;
	char	**envp;

	i = 0;
	cur = env_head->next; // 헤드는 빈 노드
	envp = (char **)malloc(sizeof(char *) * (count_env_node(env_head) + 1));
	if (!envp)
		return (NULL);
	while (cur)
	{
		envp[i] = ft_strdup(cur->line);
		if (!envp[i])
			return (NULL); // 추가 처리 Error
		cur = cur->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

/*
	check_path
	환경변수 PATH에 있는 경로를 찾아서 해당 명령어가 있는지 확인한다.
	만약 없다면 NULL을 반환한다.
*/
static char	*check_path(t_env *env_head, char *cmd)
{
	char *path;
	char **path_list;

	path_list = split_paths(env_head);
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

static char	**split_paths(t_env *env_head)
{
	t_env	*cur;
	char	**path_list;

	cur = env_head->next;
	while (cur && ft_strncmp("PATH=", cur->line, 5) != 0)
		cur = cur->next;
	path_list = ft_split(cur->line + 5, ':');
	if (!path_list)
		return (NULL);
	return (path_list);
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
