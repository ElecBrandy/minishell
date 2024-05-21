/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_without_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:20:54 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 18:41:15 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sort_arr_2d(char **arr);

void export_withoutarg(t_env *env)
{
	int			i;
	char		**str;
	char		*sep_pos;
	t_envutil	util;

	str = env_list_to_array(env);
	if (str == NULL)
		return ; // Error
	sort_arr_2d(str);
	i = 0;
	while(str[i])
	{
		printf("declare -x ");
		sep_pos = ft_strchr(str[i], '=');
		if (sep_pos == NULL) // 첫번째 '='가 존재하지 않는 경우
		{
			printf("%s\n", str[i]);
		}
		else // 첫번째 '='가 존재하는 경우
		{
			if (*sep_pos + 1 == '\0') // value가 존재하지 않는 경우 (= 이 마지막인 경우)
			{
				printf("%s\"\"\n", str[i]);
			}
			else // value가 존재하는 경우 (= 이 마지막이 아닌 경우)
			{
				util.key = ft_substr(str[i], 0, sep_pos - str[i]); // Error
				util.value = ft_strdup(sep_pos + 1); // Error
				if (!util.key || !util.value)
					exit(1); // Error
				printf("%s=\"%s\"\n", util.key, util.value);
				ft_free((void **)&util.key);
				ft_free((void **)&util.value);
			}
		}
		i++;
	}
}

static int	sort_arr_2d(char **arr)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (arr[i])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) > 0)
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (TRUE);
}