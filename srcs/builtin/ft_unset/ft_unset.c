/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:38 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 14:51:08 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unset_witharg(t_env *env, t_node *node);
static void	delete_env(t_env *env, char *key);

void	ft_unset(t_env *head_env, t_node *node)
{
	if (ft_arrlen_2d(node->cmd) == 1) // 인자가 없는 경우
	{
		exit(1); // Error: unset: not enough arguments
	}
	else // 인자가 있는 경우 (key)
	{
		unset_witharg(head_env, node);
	}
	exit(0);
}

// 인자를 순회하며
static void	unset_witharg(t_env *head_env, t_node *node)
{
	int     i;
	char    *key;
	char    *value;

	i = 1;
	while (node->cmd[i]) // 인자를 순회하며 인자를 검사. 이상한 인자가 있을 경우 에러 메세지 출력하고 이어서 검사 (끝까지 동작함!)
	{
		// 인자의 조건 : 오로지 key 형식이어야함
		if (!is_valid_key(node->cmd[i])) // 인자가 유효하지 않은 경우
		{
			printf("minishell: unset: `%s': not a valid identifier\n", node->cmd[i]); // Error 메세지 출력
		}
		else // 인자가 문제 없는 경우 (다중 삭제 가능)
		{
			delete_env(head_env, node->cmd[i]); // 존재하는 경우 삭제(없으면 그냥 패스)
		}
		i++;
	}
}

static void	delete_env(t_env *head_env, char *key)
{
	t_env	*cur;
	t_env	*prev;

	cur = head_env;
	prev = NULL;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(key) \
		 && ft_strncmp(cur->key, key, ft_strlen(key)) == 0) // key가 일치하는 경우 찾고
		{
			if (prev) // 중간 노드 삭제
				prev->next = cur->next;
			else // 첫 노드 삭제
				head_env = cur->next;
			ft_free((void **)&cur->key); // key 메모리 해제
			ft_free((void **)&cur->value); // value 메모리 해제
			ft_free((void **)&cur); // 노드 메모리 해제
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
