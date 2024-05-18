/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/18 16:22:31 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_export(t_env *env, t_node *node)
{
	int	i;

	if (node->cmd[1] != NULL) // 인자가 없는 경우
	{
		export_withoutarg(env);
	}
	else // 인자가 있는 경우 (key)
	{
		export_witharg(env, node);
	}
	exit(0);
}
