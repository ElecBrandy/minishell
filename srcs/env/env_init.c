/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 20:03:45 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_str(char **str);
static int	sort_arr_2d(char **arr);
static int	copy_array(char **src, char **dst);
static void	print_arry_2d(char **arr); // Error (나중에 지우기)


// static void	print_arry_2d(char **arr)
// {
// 	int i;

// 	i = 0;
// 	fprintf(stderr, "asdfsadfasdfasdfasdfasdfasdfasdfasfdasfdas\n");
// 	while (arr[i])
// 	{
// 		fprintf(stderr, "%s\n", arr[i]);
// 		i++;
// 	}
// }

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

static int	copy_array(char **src, char **dst)
{
	int i;

	i = 0;
	// if (!src || !dst)
	// 	return (FALSE);
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

