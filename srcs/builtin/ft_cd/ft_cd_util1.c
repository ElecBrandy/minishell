/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:55:25 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 19:08:07 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	update_pwd(t_env **env, char *cur_path)
{
	t_env	*cur;
	char	*new_cmd;

	cur = is_env(*env, "PWD");
	if (!cur)
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
			return (1);
		add_env(env, new_cmd, "PWD", cur_path);
	}
	else
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
			return (1);
		renew_env(cur, new_cmd, cur_path);
	}
	ft_free((void **)&new_cmd);
	return (0);
}

int	update_oldpwd(t_env **env, char *cur_path)
{
	t_env	*cur;
	char	*new_cmd;

	cur = is_env(*env, "OLDPWD");
	if (!cur)
	{
		new_cmd = ft_strjoin("OLDPWD=", cur_path);
		if (!new_cmd)
			return (1);
		add_env(env, new_cmd, "OLDPWD", cur_path);
	}
	else
	{
		new_cmd = ft_strjoin("OLDPWD=", cur_path);
		if (!new_cmd)
			return (1);
		renew_env(cur, new_cmd, cur_path);
	}
	ft_free((void **)&new_cmd);
	return (0);
}

t_env	*is_env(t_env *env, char *key)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
