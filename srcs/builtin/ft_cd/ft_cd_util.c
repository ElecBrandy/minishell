/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:55:25 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:47:58 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	cd_error_print(char *path, char *log);

int	update_pwd(t_env **env, char *cur_path)
{
	t_env	*cur;
	char	*new_cmd;

	cur = is_env(*env, "PWD");
	if (!cur)
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
			return (FALSE);
		add_env(env, new_cmd, "PWD", cur_path);
	}
	else
	{
		new_cmd = ft_strjoin("PWD=", cur_path);
		if (!new_cmd)
			return (FALSE);
		renew_env(cur, new_cmd, cur_path);
	}
	ft_free((void **)&new_cmd);
	return (TRUE);
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
			return (FALSE);
		add_env(env, new_cmd, "OLDPWD", cur_path);
	}
	else
	{
		new_cmd = ft_strjoin("OLDPWD=", cur_path);
		if (!new_cmd)
			return (FALSE);
		renew_env(cur, new_cmd, cur_path);
	}
	ft_free((void **)&new_cmd);
	return (TRUE);
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

void	ft_cd_error(int error, char *path)
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

static void	cd_error_print(char *path, char *log)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(log, 2);
	ft_putstr_fd("\n", 2);
}
