/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_with_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:21:36 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 17:53:04 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	export_witharg(t_env **head_env, t_node *node)
{
	int			i;
	t_envutil	util;
	t_env		*cur;

	i = 0;
	while (node->cmd[++i])
	{
		util.tmp = ft_strdup(node->cmd[i]);
		if (!util.tmp)
			return (12);
		parse_env_str(util.tmp, &util.key, &util.value);
		if (is_valid_key(util.key) == FALSE
			|| is_valid_value(util.value) == FALSE)
		{
			ft_free((void **)&util.tmp);
			return (ft_export_error(2, node->cmd[i]));
		}
		cur = is_env(*head_env, util.key);
		if (!cur)
			add_env(head_env, node->cmd[i], util.key, util.value);
		else
			renew_env(cur, node->cmd[i], util.value);
		ft_free((void **)&util.tmp);
	}
	return (0);
}

int	renew_env(t_env *cur, char *cmd, char *value)
{
	if (ft_strchr(cmd, '=') == NULL)
		return (0);
	else
	{
		ft_free((void **)&cur->cmd);
		ft_free((void **)&cur->value);
		if (value)
		{
			cur->cmd = ft_strdup(cmd);
			cur->value = ft_strdup(value);
			if (!cur->cmd || !cur->value)
			{
				ft_free((void **)&cur->cmd);
				ft_free((void **)&cur->value);
				return (12);
			}
		}
	}
	return (0);
}

// int	add_env(t_env *head_env, char *cmd, char *key, char *value)
// {
// 	t_env	*cur;
// 	t_env	*new_node;

// 	cur = head_env;
// 	new_node = create_node_env(cmd, key, value);
// 	if (!new_node)
// 		return (12);
// 	append_node_env(&cur, new_node);
// 	return (0);
// }

int	add_env(t_env **head_env, char *cmd, char *key, char *value)
{
	t_env	*new_node;

	if (!head_env)
		return (1); // 포인터의 포인터 자체가 NULL이면 에러 반환
	new_node = create_node_env(cmd, key, value);
	if (!new_node)
		return (12);
	if (*head_env == NULL) {
		*head_env = new_node; // head_env가 NULL이면 새 노드를 헤드로 설정
	} else {
		append_node_env(head_env, new_node); // 기존 리스트에 노드 추가
	}
	return (0);
}

