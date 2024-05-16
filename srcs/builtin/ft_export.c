/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 20:42:46 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_2d_array(char **str);
// static void	sort_2d_array(char **str);
// static int str_compare(const char *s1, const char *s2);
// static void swap_rows(char ***array, int row1, int row2);

void ft_export(t_env *env, t_node *node)
{
	// int i;

	// i = 0;
	// if (!env->arr_export)
	// {
	// 	exit(1); // Error
	// }
	// if (ft_strlen(node->cmd[0]) == 6 && ft_strncmp(node->cmd[0], "export", 6) == 0) // 오직 export 만 들어온 경우
	// {
	// 	while (env->arr_export[i])
	// 	{
	// 		printf("declare -x %s\n", env->arr_export[i]);
	// 		i++;
	// 	}
	// }
	// else // export 다음에 변수가 들어온 경우
	// {
		printf("add ENV\n");	// 여기서 변수를 추가해주는 작업을 해야함
	// }
	exit(1);
}

/*
	export a=123
	
	node
	cmd[0] = export
	cmd[1] = a=123


	입력 예시
	export a -> 대상없는 export 에서는 출력 / env에서는 미출력
	export a= -> a=""
	export a=123 -> a="123"

	이미 있는 변수에 대해서는 덮어쓰기	
	export a=123 -> a="123" // a가 이미 존재할 경우
	export a= -> a="" // a가 이미 존재할 경우
	export a -> (아무일도 일어나지 않음) // a가 이미 존재할 경우

*/

// key와 value는 첫번째 '='를 기준으로 나눠야함

char	*add_env(t_env *env, t_node *node)
{
	char *key;
	char *value;
	char *p_equal;

	p_equal = ft_strchr(node->cmd[1], '=');
	if (p_equal == NULL) // '=' 없는 경우
	{
		key = ft_strdup(node->cmd[1]);
		value = ft_strdup("");
	}
	else // '=' 있는 경우
	{
		key = ft_substr(node->cmd[1], 0, p_equal - node->cmd[1]);
		if (!key)
			return (NULL); // Error
		value = ft_strdup(p_equal + 1);
		if (!value)
			return (NULL); // Error
	}
	printf("=== add_env ===\n");
	printf("key : %s\n", key);
	printf("value : %s\n", value);
	return (key); // Error
}
