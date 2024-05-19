/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/19 16:55:53 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_env *env, t_node *node)
{
	int	i;

	if (count_2d_array(node->cmd) == 1) // 인자가 없는 경우
	{
		export_withoutarg(env); // 정상작동 확인
	}
	else // 인자가 있는 경우 (key)
	{
		export_witharg(env, node);
	}
	exit(0);
}
