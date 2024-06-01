/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:31:14 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:11:49 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_node_env(char *cmd, char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->cmd = ft_strdup(cmd);
	new_node->key = ft_strdup(key);
	if (value == NULL)
		new_node->value = ft_strdup("");
	else if (value[0] == '\0')
		new_node->value = ft_strdup("");
	else
		new_node->value = ft_strdup(value);
	new_node->next = NULL;
	if (!new_node->cmd || !new_node->key || !new_node->value)
	{
		ft_free((void **)&new_node->cmd);
		ft_free((void **)&new_node->key);
		ft_free((void **)&new_node->value);
		ft_free((void **)new_node);
		return (NULL);
	}
	return (new_node);
}

void	append_node_env(t_env **head, t_env *new_node)
{
	t_env	*cur;

	cur = *head;
	if (!cur)
		(*head) = new_node;
	else
	{
		while (cur->next)
			cur = cur->next;
		cur->next = new_node;
	}
}

int	add_env_to_list(t_env **head, char *ori, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_node_env(ori, key, value);
	if (!new_node)
		return (FALSE);
	append_node_env(head, new_node);
	return (TRUE);
}

void	parse_env_str(char *env_str, char **key, char **value)
{
	char	*sep_pos;

	sep_pos = ft_strchr(env_str, '=');
	if (!sep_pos)
	{
		*key = env_str;
		*value = NULL;
	}
	else
	{
		*sep_pos = '\0';
		*key = env_str;
		*value = sep_pos + 1;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*cur;
	t_env	*next;

	cur = head;
	while (cur != NULL)
	{
		next = cur->next;
		ft_free((void **)&cur->cmd);
		ft_free((void **)&cur->key);
		ft_free((void **)&cur->value);
		ft_free((void **)&cur);
		cur = next;
	}
}
