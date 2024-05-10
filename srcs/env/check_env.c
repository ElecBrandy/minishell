/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:59:22 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/08 20:43:30 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	check_env
	노드 하나 안에서 환경 변수가 존재하는지 찾음
	1. node->cmd[i]를 순회하다가 '$'를 발견하면 멈춘다.
	2. 처음 등장하는 '$'부터 다음 '$' 전 or 문자열 끝까지 환경변수를 하나의 문자열로 지정한다. (char *tmp)
	3. char *tmp이 환경변수의 조건을 만족하는지 확인한다. (is_env_name)
	4. char *tmp이 기존 환경변수 리스트 안에 존재하는지 확인한다. (is_env_list)
*/

// 환경변수가 존재하는지 찾습니다. (노드 하나 안에서)
void	find_replace_env(t_env *env_head, t_node *node)
{
	size_t	i;
	char	**tmp;

	i = 1;
	while (node->cmd[i]) // node->cmd[i]를 순회한다.
	{
		if (!ft_strchr(node->cmd[i], '$')) // 만약 '$'가 존재
		{
			tmp = ft_split(node->cmd[i], '$');
			if (!tmp)
				exit(1); // Error
			check_env(env_head, tmp); // '$' 기준으로 잘린 문자열이 이제 tmp를 순회하면서 $ 기준으로 잘린 애들이 환경변수인지 검사하면 됨
		}
		i++;
	}
}

void	check_env(t_env *env_head, char **tmp)
{
	t_env	*ptr;
	size_t	i;

	i = 0;
	while (tmp[i])
	{
		// 1. 환경변수 이름 규칙을 지키고 있는가? && 2. 이미 환경변수 리스트 내에 존재하는가?
		if (!is_env(tmp[i]))
			return ;
		ptr = is_env_list(env_head, tmp[i]); // ptr : tmp[i]과 일치하는 환경변수 리스트 요소를 의미
		if (!ptr)
			replace_env(env_head, tmp[i]);
		i++;
	}
}

/*
	확인사항 1.
	is_env_name
	환경변수 이름 규칙을 지키고 있는가?
*/
int	is_env(char *str)
{
	size_t i;

	i = 0;
	if (!ft_isalpha(str[0]) && str[0] != '_') // 첫 번째 문자가 알파벳 또는 밑줄(_)이 아니면 유효하지 않음
		return (FALSE);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_') // 알파벳, 숫자, 밑줄(_)이 아니면 유효하지 않음
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
	확인사항 2.
	is_env_list
	이미 환경변수 리스트 내에 존재하는가?
*/
t_env	*is_env_list(t_env *env_head, char *str)
{
	size_t	i;
	t_env	*cur;

	cur = env_head->next;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(str) && \
		ft_strncmp(cur->key, str + 1, ft_strlen(str)) == 0)
		{
			return (TRUE);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	replace_env(t_env *env_head, char *str)
{
	t_env	*cur;
	char	*value;
	char	*tmp;
	size_t	i;

	cur = env_head->next;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(str + 1) && \
		ft_strncmp(cur->key, str + 1, ft_strlen(str + 1)) == 0)
		{
			value = ft_strdup(cur->value);
			if (!value)
				exit(1); // Error
			tmp = ft_strjoin(value, str + ft_strlen(cur->key) + 1);
			if (!tmp)
				exit(1); // Error
			ft_free((void **)&node->cmd[i]);
			node->cmd[i] = tmp;
			ft_free((void **)&value);
			break ;
		}
		cur = cur->next;
	}
}