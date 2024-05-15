/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 02:52:25 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_2d_array(char **str);
// static void	sort_2d_array(char **str);
// static int str_compare(const char *s1, const char *s2);
// static void swap_rows(char ***array, int row1, int row2);

void ft_export(t_env *env, t_node *node)
{
	int i;

	i = 0;
	if (!env->arr_export)
	{
		exit(1); // Error
	}
	if (ft_strlen(node->cmd[0]) == 6 && ft_strncmp(node->cmd[0], "export", 6) == 0) // 오직 export 만 들어온 경우
	{
		while (env->arr_export[i])
		{
			printf("declare -x %s\n", env->arr_export[i]);
			i++;
		}
	}
	else // export 다음에 변수가 들어온 경우
	{
		printf("add ENV\n");	// 여기서 변수를 추가해주는 작업을 해야함
	}
	exit(1);
}

