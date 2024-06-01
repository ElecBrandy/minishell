/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:32:06 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 18:46:03 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_cd_error1(int error, char *path)
{
	if (error == 0)
		return ;
	else
	{
		g_signal_error = 1;
		if (error == 1)
			cd_error_print("HOME", "not set");
		else if (error == 2)
			cd_error_print(path, "No such file or directory");
		else if (error == 3)
			cd_error_print(path, "Permission denied");
		else if (error == 4)
			cd_error_print(path, "Not a directory");
		else if (error == 5)
			cd_error_print("OLDPWD", "not set");
		else if (error == 6)
			cd_error_print("PWD", "not set");
		else if (error == 12)
		{
			g_signal_error = 12;
			print_error();
		}
		else
			print_error();
	}
}

void	ft_cd_error2(int error)
{
	if (error == 0)
		return ;
	else
	{
		g_signal_error = 1;
		if (error == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("Failed to update OLDPWD.\n", 2);
		}
		else if (error == 2)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("Failed to update PWD.\n", 2);
		}
		else if (error == 3)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("Failed to change directory.\n", 2);
		}
		else if (error == 12)
		{
			g_signal_error = 12;
			print_error();
		}
		else
			print_error();
	}
}

void	cd_error_print(char *path, char *log)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(log, 2);
	ft_putstr_fd("\n", 2);
}
