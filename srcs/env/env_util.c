/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:31:14 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 13:55:34 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_node_env(const char *cmd, const char *key, const char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(cmd);
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = ft_strdup("");
	else if (value[0] == '\0')
		new_node->value = ft_strdup("");
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->cmd || !new_node->key || !new_node->value)
	{
		ft_free((void **)&new_node->cmd);
		ft_free((void **)&new_node->key);
		ft_free((void **)&new_node->value);
		ft_free((void **)new_node);
		return (NULL);
	}
	return (new_node);
}

void	append_node_env(t_env **head, t_env *new_node)
{
	t_env	*cur;

	cur = *head;
	if (!cur)
		(*head) = new_node;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}

void	add_env_to_list(t_env **head, char *ori_str, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_node_env(ori_str, key, value);
	if (!new_node)
	{
		// free_env_list(*head); // 메모리 해제
		// exit(1); // 실패 시 종료
	}
	append_node_env(head, new_node);// 성공 시 리스트에 노드 추가
}

void	parse_env_str(char *env_str, char **key, char **value)
{
	char	*sep_pos;

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

void	free_env_list(t_env *head)
{
	t_env	*cur;
	t_env	*next;

	cur = head;
	while (cur != NULL)
	{
		next = cur->next;
		ft_free((void **)&cur->cmd);
		ft_free((void **)&cur->key);
		ft_free((void **)&cur->value);
		ft_free((void **)&cur);
		cur = next;
	}
}
