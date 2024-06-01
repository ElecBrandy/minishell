/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_without_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:20:54 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 18:08:52 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	print_arg(char *str, char *sep_pos);
static int	forech_arg(char **str);
static int	sort_arr_2d(char **arr);

int	export_withoutarg(t_env *env)
{
	int			error;
	char		**str;

	if (env == NULL)
		return (1);
	str = env_list_to_array(env);
	if (str == NULL)
		return (12);
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
	while (str[i])
	{
		error = print_arg(str[i], sep_pos);
		if (error != 0)
			return (error);
		i++;
	}
	return (0);
}

static int	print_arg(char *str, char *sep_pos)
{
	int			error;
	t_envutil	util;

	error = 0;
	printf("declare -x ");
	sep_pos = ft_strchr(str, '=');
	if (sep_pos == NULL)
		printf("%s\n", str);
	else
	{
		if (*sep_pos + 1 == '\0')
			printf("%s\"\"\n", str);
		else
		{
			util.key = ft_substr(str, 0, sep_pos - str);
			util.value = ft_strdup(sep_pos + 1);
			if (util.key && util.value)
				printf("%s=\"%s\"\n", util.key, util.value);
			else
				error = 12;
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
