/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 14:17:32 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_env *env, t_node *node)
{
	int	i;

	fprintf(stderr, "정상실행?\n");
	if (ft_arrlen_2d(node->cmd) == 1) // 인자가 없는 경우
	{
		fprintf(stderr, "정상실행?\n");
		export_withoutarg(env); // 정상작동 확인
	}
	else // 인자가 있는 경우 (key)
	{
		export_witharg(env, node);
	}
	exit(0);
}
