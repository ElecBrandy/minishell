/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 20:16:06 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	ft_env
	- Print the environment variables.
	- If there is no argument, print all the environment variables.
*/

static void	ft_env_error(int error);

void	ft_env(t_env *env, t_node *node)
{
	int		i;
	t_env	*cur;

	if (ft_arrlen_2d(node->cmd) != 1)
		ft_env_error(1);
	if (env == NULL)
		ft_env_error(2);
	else
	{
		cur = env;
		i = 0;
		while (cur != NULL)
		{
			if (ft_strchr(cur->cmd, '=') != NULL)
			{
				printf("%s=%s\n", cur->key, cur->value);
			}
			cur = cur->next;
		}
	}
	return ;
}

static void	ft_env_error(int error)
{
	g_signal_error = 1;
	if (error == 1)
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
	else if (error == 2)
	{
		g_signal_error = 127;
		ft_putstr_fd("minishell: env: No such file or directory\n", 2);
	}
	else
		print_error();
}
