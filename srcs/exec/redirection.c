/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:22:21 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/07 18:57:36 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* redirection '<' */
/*
	a < b
	b의 내용을 a의 표준입력으로 redriection
*/

int	is_redirection(t_node *node)
{
	size_t	i;

	i = 0;
	while (node->cmd[i])
	{
		if (ft_strncmp(node->cmd[i], "<", 1) == 0)
			return (0);
		i++;
	}
	return (1);
}
