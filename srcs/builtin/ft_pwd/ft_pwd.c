/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 17:48:20 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/31 16:50:11 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_pwd(t_env *env, t_node *node)
{
	t_env	*cur;
	char	*str;

	cur = is_env(env, "PWD");
	if (cur)
	{
		ft_putstr_fd(env->value, node->out_fd);
		write(node->out_fd, "\n", 1);
	}
	else
	{
		str = getcwd(NULL, 0);
		if (!str)
		{
			g_signal_error = 1;
			print_error();
			return ;
		}
		ft_putstr_fd(str, node->out_fd);
		write(node->out_fd, "\n", 1);
		ft_free((void **)&str);
	}
}
