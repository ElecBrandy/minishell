/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/26 20:42:15 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int run_cmd(t_env *head_env, t_node *node, char *home, pid_t pid)
{
	t_env *cur;
	char	*path;
	char	**cmd;
	char 	**tmp;

	if (!head_env)
	{
		fprintf(stderr, "env is NULL\n");
		exit(1); // Error
	}
	tmp = env_list_to_array(head_env);
	if (!tmp)
	{
		fprintf(stderr, "env is NULL\n");
		exit(1); // Error
	}
	if (execve(node->path, node->cmd, tmp) == -1)
	{
		exit(1); // Error
	}
	return (0);
}
