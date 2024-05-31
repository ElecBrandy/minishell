/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 14:19:07 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/31 18:22:12 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_env(t_env *env);
static int	env_array_to_list(t_env **env, char **envp);

void	set_home(char **envp, char **home)
{
	int		i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			*home = ft_strdup(envp[i] + 5);
			if (!*home)
			{
				g_signal_error = 12;
				print_error();
				exit(g_signal_error);
			}
		}
		i++;
	}
}

void	set_env_list(t_env **env, char **envp)
{
	if (env_array_to_list(env, envp) == FALSE)
	{
		free_env_list(*env);
		g_signal_error = 12;
		print_error();
		exit(g_signal_error);
	}
}

static int	env_array_to_list(t_env **env, char **envp)
{
	int			i;
	t_envutil	util;

	i = 0;
	while (envp[i])
	{
		util.tmp = ft_strdup(envp[i]);
		if (!util.tmp)
			return (FALSE);
		parse_env_str(envp[i], &(util.key), &(util.value));
		if (add_env_to_list(env, util.tmp, util.key, util.value) == FALSE)
		{
			ft_free((void **)&(util.tmp));
			return (FALSE);
		}
		ft_free((void **)&(util.tmp));
		i++;
	}
	return (TRUE);
}

char	**env_list_to_array(t_env *env)
{
	int		i;
	t_env	*cur;
	char	**arr;

	i = 0;
	cur = env;
	arr = (char **)malloc(sizeof(char *) * (count_env(env) + 1));
	if (!arr)
		return (NULL);
	while (cur)
	{
		arr[i] = ft_strdup(cur->cmd);
		if (!arr[i])
			return (NULL);
		i++;
		cur = cur->next;
	}
	arr[i] = NULL;
	return (arr);
}

static int	count_env(t_env *env)
{
	int		cnt;
	t_env	*cur;

	cnt = 0;
	cur = env;
	while (cur != NULL)
	{
		cnt++;
		cur = cur->next;
	}
	return (cnt);
}
