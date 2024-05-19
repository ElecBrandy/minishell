/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:27:16 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/19 16:43:56 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// \ -> 처리를 잊지말자. 일단 나중에

int is_valid_key(char *key)
{
	int i = 0;

	if (!key)
		return (FALSE);
	if (ft_isdigit(key[0])) // 첫 글자가 숫자면 유효하지 않음
		return (FALSE);
	if (!ft_isalnum(key[0]) && key[0] != '_') // 첫 글자가 알파벳 또는 언더스코어가 아니면 유효하지 않음
		return (FALSE);
	i = 1;
	while (key[i]) // 나머지 문자 검사
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int is_valid_value(char *value) // 슬래시 나중에 어떻게 할것인지 생각해보기...
{
	int i = 0;

	if (value == NULL || *value == '\0') // NULL도 유효함
		return (TRUE);
	while (value[i])
	{
		if (value[i] < 32 || value[i] == 127) // 컨트롤 문자가 포함되어 있으면 유효하지 않음
			return (FALSE);
		i++;
	}
	return (TRUE); // 위 조건에 걸리지 않으면 유효한 값
}

int is_inenv(t_env *env, char *key)
{
	t_env *cur;

	cur = env;
	while (cur)
	{
		if (ft_strlen(cur->key) == ft_strlen(key) \
		 && ft_strncmp(cur->key, key, ft_strlen(key)) == 0)
			return (TRUE);
		cur = cur->next;
	}
	return (FALSE);
}
