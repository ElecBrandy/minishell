/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 22:36:13 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	sort_arr_2d(char **arr);
static int	copy_array(char **src, char **dst);
static void	print_arry_2d(char **arr); // Error (나중에 지우기)

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
