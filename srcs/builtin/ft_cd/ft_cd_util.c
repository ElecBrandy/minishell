/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:55:25 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/23 03:48:43 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int update_pwd(t_env *head_env, char *cur_path)
{
	t_env	*cur;
	char	*new_cmd;

	cur = is_env(head_env, "PWD");
	if (!cur) // 아직 PWD가 존재하지 않는 경우
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
			return (FALSE);
		add_env(head_env, new_cmd, "PWD", cur_path);
	}
	else // 이미 PWD가 존재하는 경우
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
		{
			ft_free((void **)&new_cmd);
			return (FALSE);
		}
		renew_env(cur, new_cmd, "PWD", cur_path);
	}
	ft_free((void **)&new_cmd);
	return (TRUE);	
}

int update_oldpwd(t_env *head_env, char *cur_path)
{
	t_env	*cur;
	char	*new_cmd;

	cur = is_env(head_env, "OLDPWD");
	if (!cur) // 아직 PWD가 존재하지 않는 경우
	{
		new_cmd = ft_strjoin("OLDPWD=", cur_path);
		if (!new_cmd)
			return (FALSE);
		add_env(head_env, new_cmd, "OLDPWD", cur_path);
	}
	else // 이미 PWD가 존재하는 경우
	{
		new_cmd = ft_strjoin("OLDPWD=", cur_path);
		if (!new_cmd)
		{
			ft_free((void **)&new_cmd);
			return (FALSE);
		}
		renew_env(cur, new_cmd, "OLDPWD", cur_path);
	}
	ft_free((void **)&new_cmd);
	return (TRUE);	
}

t_env *is_env(t_env *head_env, char *key)
{
	t_env	*cur;

	cur = head_env;
	while (cur)
	{
		if (ft_strncmp(cur->key, key, ft_strlen(cur->key)) == 0)
		{
			return (cur);
		}
		cur = cur->next;
	}
	return (NULL);
}

void	ft_cd_error(int check, char *path)
{
	if (check == 1)
		cd_error_print(path, "No such file or directory");
	else if (check == 2)
		cd_error_print(path, "Permission denied");
	else if (check == 3)
		cd_error_print(path, "No such file or directory");
	else if (check == 4)
		cd_error_print(path, "not set");
	else
		ft_putstr_fd("minishell: cd: change directory failed\n", 2);
	return ;
}

void cd_error_print(char *path, char *log)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(log, 2);
	ft_putstr_fd("\n", 2);
}

