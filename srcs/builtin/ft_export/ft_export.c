/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 18:38:37 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_export(t_env *head_env, t_node *node)
{
	int	i;

	if (ft_arrlen_2d(node->cmd) == 1) // 인자가 없는 경우
	{
		export_withoutarg(head_env); // 정상작동 확인
	}
	else // 인자가 있는 경우 (key)
	{
		export_witharg(head_env, node);
	}
	// print_env_list(head_env);
}



// cd with only a relative or absolute path
// 오직 상대 또는 절대경로만 사용하는 cd

// export with no options
// 옵션이 없는 export

// unset with no options
// 옵션이 없는 unset

// exit with no options
// 옵션이 없는 exit