/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:52:46 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/28 20:55:00 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	run_cmd(t_env *head_env, t_node *node);
static char	*check_path(char **envp, char *cmd);
static char	*make_path(char **path_list, char *cmd);
static int is_onlycmd(char *cmd);

int	ft_execve(t_env **head_env, t_node *node, char *home, pid_t pid)
{
	int	error;

	if (is_builtin(node) != 0)
		exec_builtin(head_env, node, home, pid);
	else
	{
		error = run_cmd(*head_env, node);
		if (error == 88)
			g_signal_error = 12;
		print_error();
	}
	exit(g_signal_error);
}

static int run_cmd(t_env *head_env, t_node *node)
{
	char	*path;
	char	**envp;

	envp = env_list_to_array(head_env);
	if (!envp)
		return (88);
	path = check_path(envp, node->cmd[0]);
	if (!path)
		return (88);
	if (execve(path, node->cmd, envp) == -1)
		return (127);
	return (0);
}

static char *check_path(char **envp, char *cmd)
{
	char	*path;
	char	**path_list;

	while (*envp && ft_strncmp("PATH=", *envp, 5) != 0)
		envp++;
	path_list = ft_split(*envp + 5, ':');
	if (!path_list)
		return (NULL);
	path = make_path(path_list, cmd);
	if (!path)
		return (NULL);
	return (path);
}

static char *make_path(char **path_list, char *cmd)
{
	char	*tmp;
	char	*path;

	if (is_onlycmd(cmd) == TRUE)
	{
		while (*path_list)
		{
			tmp = ft_strjoin(*path_list, "/");
			if (!tmp)
				return (NULL);
			path = ft_strjoin(tmp, cmd);
			ft_free((void **)&tmp);
			if (!path)
				return (NULL);
			if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
				return (path);
			ft_free((void **)&path);
			path_list++;
		}
	}
	if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		return (cmd);
	return (NULL);
}

static int is_onlycmd(char *cmd)
{
	if (cmd == NULL)
		return (TRUE);
	if (cmd[0] == '/')
		return (FALSE);
	if (ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (FALSE);
	return (TRUE);
}

// void	is_inchild(char *cmd)
// {
// 	char	**cmds;
	
// 	cmds = malloc(sizeof(char *) * (18));
// 	cmds[17] = NULL;

// 	cmds[0] = ft_strdup("wc");
// 	cmds[1] = ft_strdup("cmp");
// 	cmds[2] = ft_strdup("awk");
// 	cmds[3] = ft_strdup("split");
// 	cmds[4] = ft_strdup("cat");
// 	cmds[5] = ft_strdup("cut");
// 	cmds[6] = ft_strdup("sed");
// 	cmds[7] = ft_strdup("tr");
// 	cmds[8] = ft_strdup("diff");
// 	cmds[9] = ft_strdup("diff3");
// 	cmds[10] = ft_strdup("grep");
// 	cmds[11] = ft_strdup("egrep");
// 	cmds[12] = ft_strdup("fgrep");
// 	cmds[13] = ft_strdup("head");
// 	cmds[14] = ft_strdup("tail");
// 	cmds[15] = ft_strdup("rev");
// 	cmds[16] = ft_strdup("sort");
// 	cmds[17] = NULL;
// 	check_cmds(cmds, cmd);
// 	free_str(cmds);
// }

// static int	check_cmds(char **cmds, char *cmd)
// {
// 	int	i;

// 	i = -1;
// 	while (cmds[++i])
// 	{
// 		if (ft_find_word(cmd, cmds[i]))
// 		{
// 			signal(SIGINT, child_handler);
// 			signal(SIGQUIT, child_handler);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// static int	ft_find_word(char *str, char *word)
// {
// 	int	i;
// 	int	j;
// 	int	start;

// 	i = -1;
// 	while (str[++i])
// 	{
// 		start = 0;
// 		if (str[i] == word[start])
// 		{
// 			j = i;
// 			while (str[++j])
// 			{
// 				if (word[start] == '\0')
// 					return (1);
// 				if (str[j] != word[++start])
// 					break ;
// 			}
// 		}
// 	}
// 	return (0);
// }
