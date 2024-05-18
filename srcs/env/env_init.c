/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/18 16:14:42 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env *env_array_to_list(t_env *head, char **envp)
{
    int		i;
    char	*key;
	char	*value;
	char	*temp;

	i = 0;
    head = NULL;
    while (envp[i])
	{
        temp = ft_strdup(envp[i]); // 원본 문자열 복사 // 나중에 제대로 작동한다면, 이 복사본 temp가 과연 필요한지 확인해보기
        parse_env_str(temp, &key, &value); //key와 value 추출
        add_env_to_list(&head, temp, key, value); // 파싱 성공 시 노드 추가
        ft_free((void **)&temp); // 사용한 임시 문자열 메모리 해제
        i++;
    }
    return head;
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
		arr[i] = ft_strdup(cur->cmd); // Error?
		// printf("arr[%d]: %s\n", i, arr[i]);
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}

void	parse_env_str(char *env_str, char **key, char **value)
{
    char *sep_pos;

	sep_pos = ft_strchr(env_str, '=');
	if (!sep_pos) // '=' 이 없을 경우
	{
		*key = env_str;
		*value = NULL;
	}
	else // '=' 이 있을 경우
	{
		*sep_pos = '\0'; // '='를 NULL 문자로 변경하여 문자열 분리
		*key = env_str; // 키는 '=' 이전 부분
		*value = sep_pos + 1; // 값은 '=' 다음 부분
	}
}
