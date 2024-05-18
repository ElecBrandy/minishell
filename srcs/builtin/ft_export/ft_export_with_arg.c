/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_with_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:21:36 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/18 17:01:34 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	export_witharg(t_env *env, t_node *node)
{
	int     i;
    char    *key;
    char    *value;

	i = 1;
	while (node->cmd[i])
	{
        parse_env_str(node->cmd[i], &key, &value);
		if (!is_valid_key(key) && !is_valid_value(value))
		{
			exit(1); // Error, bash: export: `-n': not a valid identifier
		}
		else // 인자가 문제 없는 경우
		{
			if (is_inenv(env, key)) // 환경변수 리스트 내 존재?
				renew_env(env, key, value); // 존재하는 경우 갱신
			else
				add_env(env, node->cmd[i], key, value); // 존재하지 않는 경우 추가
		}
	}
}

void    renew_env(t_env *env, char *key, char *value)
{
    t_env *cur;

    cur = env;
    while (cur)
    {
        if (ft_strlen(cur->key) == ft_strlen(key) \
         && ft_strncmp(cur->key, key, ft_strlen(key)) == 0) // key가 일치하는 경우 찾고
        {
            ft_free((void **)&cur->value); // 기존 value 메모리 해제
            if (value) // 만약 value가 NULL 인경우 ('=' 없이 입력된 경우) -> 무시 / "" or 정상일 경우 renew
            {   
                cur->value = ft_strdup(value);
            }
            return ;
        }
        cur = cur->next;
    }
}

void    add_env(t_env *env, char *cmd, char *key, char *value)
{
    t_env *cur;
    t_env *new_node;

    cur = env;
    new_node = create_node_env(cmd, key, value);
    if (!new_node)
    {
        // free_env_list(env); // 메모리 해제
        exit(1); // 실패 시 종료
    }
    append_node_env(&cur, new_node); // 뒤에 추가
}
