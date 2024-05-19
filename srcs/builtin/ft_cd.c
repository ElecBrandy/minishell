/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:26 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/19 18:06:22 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
	ft_cd
	cd with only a relative or absolute path
*/

void ft_cd(t_env *head_env, t_node *node)
{
	int	i;

	if (count_2d_array(node->cmd) == 1) // 인자가 없는 경우 "cd" : 오류
	{
		// bash에서 
		exit(1); // Error
	}
	else // 인자가 있는 경우 (key)
	{
		export_witharg(env, node);
	}
	exit(0);
}

