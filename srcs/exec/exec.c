/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/27 18:54:36 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_cmd(t_env *head_env, t_node *node, char *home, pid_t pid)
{
	char	**tmp;

	if (!head_env)
		exit (12);
	tmp = env_list_to_array(head_env);
	if (!tmp)
		exit (12);
	if (execve(node->path, node->cmd, tmp) == -1)
		exit (12);
	exit (0);
}
