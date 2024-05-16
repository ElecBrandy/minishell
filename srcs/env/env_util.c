/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:31:14 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 20:04:58 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data *create_node_env(const char *cmd, const char *key, const char *value)
{
	t_data *new_node;

	new_node = (t_data *)malloc(sizeof(t_data));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(cmd);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->cmd || !new_node->key|| !new_node->value)
	{
		ft_free((void **)&new_node->cmd);
		ft_free((void **)&new_node->key);
		ft_free((void **)&new_node->value);
		ft_free((void **)new_node);
		return (NULL);
	}
	return (new_node);
}

void	append_node_env(t_data **head, t_data *new_node)
{
	t_data	*cur;

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

t_data *envp_to_linkedlist(t_data *head, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*sep_pos;
	t_data	*new_node;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		sep_pos = strchr(envp[i], '=');  // '=' 위치 찾기
		if (sep_pos)
		{
			*sep_pos = '\0';								// '=' 기호를 NULL로 바꿔 key와 value를 분리
			key = envp[i];									// 키는 '=' 이전 부분
			value = sep_pos + 1;							// 값은 '=' 다음 부분
			new_node = create_node_env("env", key, value);	// 새로운 노드 생성 및 연결 리스트에 추가
			if (new_node)									// 노드 생성에 성공한 경우만 추가
				append_node_env(&head, new_node);
		}
		i++;
	}
	return (head);
}

void print_env_list(t_data *head)
{
	if (head == NULL) {
		printf("The list is empty.\n");
		return;
	}

	t_data *cur = head;
	while (cur != NULL) {
		printf("=== env ===\n");
		printf("command: %s\n", cur->cmd);
		printf("key: %s\n", cur->key);
		printf("value: %s\n", cur->value);
		printf("\n");
		cur = cur->next;
	}
}

char **env_to_arr(t_env *head_env)
{
	int i;
	t_data *cur;
	char **arr;

	i = 0;
	cur = head_env;
	arr = (char **)malloc(sizeof(char *) * (count_str(head_env) + 1));
	if (!arr)
		return (NULL);
	while (cur)
	{
		arr[i] = ft_strdup(cur->cmd);
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}