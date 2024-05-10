/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 15:47:35 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_env(t_env *env_head)
{
	t_env	*cur;
	
	cur = env_head->next; // 첫번째 노드는 환경변수가 아니므로(헤드니까)
	if (cur == NULL)
		exit (1); // Error?
	while (cur != NULL)
	{
		printf("%s\n", cur->line);
		cur = cur->next;
	}
	exit(0); // Error?
}

