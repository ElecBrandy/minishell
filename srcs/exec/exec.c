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

static void	exec_cmd(t_env *head_env, t_node *node);
// static int	check_cmds(char **cmds, char *cmd);
// static int	ft_find_word(char *str, char *word);

int run_cmd(t_env *head_env, t_node *node, char *home, pid_t pid)
{
	t_env *cur;

	if (is_builtin(node) != 0) // builtin 일 경우
	{
		exec_builtin(head_env, node, home, pid);
		exit(0); // Error? : 정상종료
	}
	else // builtin 아니라 일반 함수인 경우
	{
		// cur = is_env(head_env, "PATH");
		// if (cur->value[0] == '\0')
		// {
		// 	ft_putstr_fd("minishell: ", 2);
		// 	ft_putstr_fd(node->cmd[0], 2);
		// 	ft_putstr_fd(": No such file or directory\n", 2);
		// 	exit(1); // Error
		// }
		exec_cmd(head_env, node); // 환경변수단에 넣어보고 일단 실행
	}
	return (0);
}

// cmd 실행
void exec_cmd(t_env *head_env, t_node *node)
{
	char 	**tmp;

	if (!head_env)
	{
		exit(1); // Error
	}
	tmp = env_list_to_array(head_env);
	if (!tmp)
	{
		exit(1); // Error
	}
	if (execve(node->path, node->cmd, tmp) == -1)
	{
		exit(1); // Error
	}
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
