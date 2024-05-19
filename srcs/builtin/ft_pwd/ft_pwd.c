/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:48:20 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/19 17:50:41 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd(t_node *node)
{
	char	*str;

	g_errnum = 0; // 이거 어떻게 하지?
	// Error? 전역변수
	str = getcwd(NULL, 0);
	if (!str)
	{
		ft_putstr_fd("error?\n", 2); // Error?
		exit(1); // Error?
	}
	ft_putstr_fd(str, node->out_fd);
	write(node->out_fd, "\n", 1);
	ft_free((void **)&str);
	exit(0);
}
