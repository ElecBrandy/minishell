/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 17:59:25 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	ft_env
	- Print the environment variables.
	- If there is no argument, print all the environment variables.
*/

void	ft_env(t_env *head_env, t_node *node)
{
	int		i;
	t_env	*cur;
	char	**env;

	if (ft_arrlen_2d(node->cmd) != 1) // 옵션 또는 인자가 있는 경우
	{
		printf("minishell: env: %s: No such file or directory\n", node->cmd[1]);
		return ; // Error
	}
	else // 옵션 || 인자가 없는 경우 (정상 : 환경변수 출력)
	{
		cur = head_env;
		i = 0;
		while (cur != NULL)
		{
			if (ft_strchr(cur->cmd, '=') != NULL) // '='가 존재하는 경우만 (출력 O)
			{
				printf("%s=%s\n", cur->key, cur->value);
			}
			cur = cur->next;
		}
	}
}
