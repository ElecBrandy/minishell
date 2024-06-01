/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:48:20 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 19:09:45 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(void)
{
	char	buff[PATH_MAX];

	if (getcwd(buff, PATH_MAX) == NULL)
	{
		g_signal_error = 1;
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("Failed to get current directory.\n", 2);
	}
	else
	{
		ft_putstr_fd(buff, 2);
		write(1, "\n", 1);
	}
}

