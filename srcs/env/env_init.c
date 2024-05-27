/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/27 19:40:02 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env(t_env *head_env);

t_env *env_array_to_list(t_env *head_env, char **envp, char **home)
{
	int		i;
	char	*key;
	char	*value;
	char	*temp;

	i = 0;
	head_env = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			*home = ft_strdup(envp[i] + 5); // HOME 환경변수 값 저장
		}
		temp = ft_strdup(envp[i]); // 원본 문자열 복사 // 나중에 제대로 작동한다면, 이 복사본 temp가 과연 필요한지 확인해보기
		parse_env_str(envp[i], &key, &value); //key와 value 추출
		add_env_to_list(&head_env, temp, key, value); // 파싱 성공 시 노드 추가
		ft_free((void **)&temp); // 사용한 임시 문자열 메모리 해제
		i++;
	}
	return (head_env);
}

char	**env_list_to_array(t_env *head_env)
{
	int		i;
	t_env	*cur;
	char	**arr;

	i = 0;
	cur = head_env;
	arr = (char **)malloc(sizeof(char *) * (count_env(head_env) + 1));
	if (!arr)
		return (NULL);
	while (cur)
	{
		arr[i] = ft_strdup(cur->cmd);
		if (!arr[i])
			return (NULL);
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}

static int	count_env(t_env *head_env)
{
	int		cnt;
	t_env	*cur;

	cnt = 0;
	cur = head_env;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	return (cnt);
}
