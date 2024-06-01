/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:22:15 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 15:53:21 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	ft_export
	- Export the environment variable.
	- If there is no argument, print the environment variable.

	error_log
	- 0 : Success
	- 1 : minishell: export: No such file or directory (no envp)
	- 2 : minishell: export: `%s': not a valid identifier (invalid key or value)
	- 12 : malloc error (shell not exited)
	- ex : perror (shell exited)
*/

void	ft_export(t_env **env, t_node *node)
{
	int	error;

	if (ft_arrlen_2d(node->cmd) == 1)
	{
		error = export_withoutarg(*env);
		if (error != 0)
			ft_export_error(error, NULL);
	}
	else
	{
		error = export_witharg(env, node);
		if (error != 0)
			ft_export_error(error, NULL);
	}
}

int	ft_export_error(int error, char *path)
{
	if (error == 1)
	{
		g_signal_error = 1;
		ft_putstr_fd("minishell: export: No such file or directory\n", 2);
	}
	else if (error == 2)
	{
		g_signal_error = 1;
		ft_putstr_fd("minishell: export: `", 2);
		if (path)
			ft_putstr_fd(path, 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (error == 12)
	{
		g_signal_error = 12;
		print_error();
	}
	else
		print_error();
	return (0);
}
