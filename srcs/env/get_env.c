/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/10 15:50:00 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*get_env(t_env *env_head, char **envp)
{
	size_t	i;
	t_env	*new;
	char	**tmp;

	i = 0;
	while (envp[i])
	{
		new = create_env_node(envp[i]);
		if (!new)
			exit(1); // Error
		new->line = ft_strdup(envp[i]);
		if (!new->line)
			exit(1); // Error
		tmp = ft_split(envp[i], '=');
		if (!tmp)
			exit(1); // Error
		new->key = tmp[0];
		new->value = tmp[1];
		add_env_node_backward(&env_head, new);
		i++;
	}
	return (env_head);
}

