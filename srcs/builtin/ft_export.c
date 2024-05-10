/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 16:46:56 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sort_2d_array(char **str);
static int str_compare(const char *s1, const char *s2);
static void swap_rows(char ***array, int row1, int row2);

void ft_export(t_env *env_head, t_node *node)
{
	size_t i;
	char **tmp;

	i = 0;
	tmp = env_to_char(env_head);
	if (!tmp)
		exit(1); // Error
	sort_2d_array(tmp);
	while (tmp[i])
	{
		printf("declare -x %s\n", tmp[i]);
		i++;
	}
	exit(0);
}

static void	sort_2d_array(char **str)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 1;
		while (str[j])
		{
			if (str_compare(str[i], str[j]) > 0) // 비교하는 부분
			{
				swap_rows(str, i, j); // 바꾸는 부분
			}
			j++;
		}
		i++;
	}
}

static int str_compare(const char *s1, const char *s2)
{
	int		tmp;
	size_t	len1;
	size_t	len2;
	size_t min_len;
	
	len1 = strlen(s1);
	len2 = strlen(s2);
	if (len1 < len2)
		min_len = len1;
	else
		min_len = len2;
	if (tmp == 0) // 만약 지정된 길이 내에서 동일하다면
	{
		if (len1 < len2)
			return -1;  // s1이 더 짧으면
		else if (len1 > len2)
			return 1;  // s2가 더 짧으면
	}
	return (tmp);  // 다른 경우 비교 결과 반환
}

static void swap_rows(char ***array, int row1, int row2) {
    char *tmp = array[row1];
    array[row1] = array[row2];
    array[row2] = tmp;
}
