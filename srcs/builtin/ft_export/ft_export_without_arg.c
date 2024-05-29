/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_without_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:20:54 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/27 21:10:10 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	print_arg(char *str, char *sep_pos);
static int	forech_arg(char **str);
static int	sort_arr_2d(char **arr);

int	export_withoutarg(t_env *head_env)
{
	int			error;
	char		**str;

	if (head_env == NULL)
		return (1);
	str = env_list_to_array(head_env);
	if (str == NULL)
		return (88);
	sort_arr_2d(str);
	error = forech_arg(str);
	if (error != 0)
		return (error);
	ft_free_2d(str);
	return (error);
}

static int	forech_arg(char **str)
{
	int			i;
	int			error;
	char		*sep_pos;

	i = 0;
	sep_pos = NULL;
	while(str[i])
	{
		error = print_arg(str[i], sep_pos);
		if (error != 0)
			return (error);
		i++;
	}
	return (0);
}

static int print_arg(char *str, char *sep_pos)
{
	int			error;
	t_envutil	util;

	error = 0;
	printf("declare -x ");
	sep_pos = ft_strchr(str, '=');
	if (sep_pos == NULL) // 첫번째 '='가 존재하지 않는 경우
		printf("%s\n", str);
	else // 첫번째 '='가 존재하는 경우
	{
		if (*sep_pos + 1 == '\0') // value가 존재하지 않는 경우 (= 이 마지막인 경우)
			printf("%s\"\"\n", str);
		else // value가 존재하는 경우 (= 이 마지막이 아닌 경우)
		{
			util.key = ft_substr(str, 0, sep_pos - str); // Error
			util.value = ft_strdup(sep_pos + 1); // Error
			if (util.key && util.value)
				printf("%s=\"%s\"\n", util.key, util.value);
			else
				error = 88;
			ft_free((void **)&util.key);
			ft_free((void **)&util.value);
		}
	}
	return (error);
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


// int	export_withoutarg(t_env *head_env)
// {
// 	int			i;
// 	char		**str;
// 	char		*sep_pos;
// 	t_envutil	util;

// 	if (head_env == NULL)
// 		return (1);
// 	str = env_list_to_array(head_env);
// 	if (str == NULL)
// 		return (88);
// 	sort_arr_2d(str);
// 	i = 0;
// 	while(str[i])
// 	{
// 		printf("declare -x ");
// 		sep_pos = ft_strchr(str[i], '=');
// 		if (sep_pos == NULL) // 첫번째 '='가 존재하지 않는 경우
// 			printf("%s\n", str[i]);
// 		else // 첫번째 '='가 존재하는 경우
// 		{
// 			if (*sep_pos + 1 == '\0') // value가 존재하지 않는 경우 (= 이 마지막인 경우)
// 				printf("%s\"\"\n", str[i]);
// 			else // value가 존재하는 경우 (= 이 마지막이 아닌 경우)
// 			{
// 				util.key = ft_substr(str[i], 0, sep_pos - str[i]); // Error
// 				util.value = ft_strdup(sep_pos + 1); // Error
// 				if (!util.key || !util.value)
// 					exit(1); // Error
// 				printf("%s=\"%s\"\n", util.key, util.value);
// 				ft_free((void **)&util.key);
// 				ft_free((void **)&util.value);
// 			}
// 		}
// 		i++;
// 	}
// 	ft_free_2d(str);
// }