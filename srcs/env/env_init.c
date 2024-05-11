/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/11 18:16:07 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_str(char **str);
static int	copy_array(char **src, char **dst);

int	env_init(t_env *env, char **envp)
{
	if (!envp)
		return (FALSE);
	if (!copy_array(envp, env->arr))
		return (FALSE);
	if (!copy_array(envp, env->arr_export))
		return (FALSE);
	return (TRUE);
}

static int	copy_array(char **src, char **dst)
{
	int i;

	i = 0;
	if (!src || !dst)
		return (FALSE);
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			while (--i >= 0)
				ft_free((void **)&dst[i]);
			return (FALSE);
		}
		i++;
	}
	dst[i] = NULL;
	return (TRUE);
}

static int count_str(char **str)
{
	int count;

	count = 0;
	if (str == NULL)
		return (FALSE);
	while (*str) // 포인터가 가리키는 곳이 NULL이 아닐 때까지 반복
	{
		count++;
		str++; // 다음 문자열 포인터로 이동
	}
	return (count); // 문자열의 개수 반환
}

