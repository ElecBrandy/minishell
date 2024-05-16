/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_in_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:26:26 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/16 19:13:07 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	is_outfd(char **str, int *i, t_node *node)
{
	if (!str[(*i) + 1])
		perror("no");
	else
	{
		if (str[(*i) + 1][0] == '<' || str[(*i) + 1][0] == '>')
		{
			perror("not file out");
			return ;
		}
		if (ft_strlen(str[*i]) == 1)
			new_file(str, i, node);
		else if (str[*i][1] == '>')
			append_file(str, i, node);
		else
		{
			if (node->out_fd != 1)
				close(node->out_fd);
			perror("notfile error");
		}
	}
}

char	**find_fd(char **str, t_node *node, t_env e)
{
	char	**cmd;
	int		i;
	int		idx;

	idx = 0;
	i = -1;
	while (str[idx])
		idx++;
	cmd = malloc(sizeof(char *) * (idx + 1));
	idx = 0;
	while (str[++i])
	{
		if (ft_strncmp(str[i], "<", 1) == 0)
			is_infd(str, &i, node, e);
		else if (ft_strncmp(str[i], ">", 1) == 0)
			is_outfd(str, &i, node);
		else
			cmd[idx++] = ft_strdup(str[i]);
	}
	cmd[idx] = NULL;
	free_str(str);
	return (cmd);
}

int	get_flagcnt(char *av)
{
	t_util	u;

	util_init(&u);
	while (av[++u.i])
	{
		if ((av[u.i] == '<' || av[u.i] == '>')
			&& (av[u.i + 1] != '<' && av[u.i + 1] != '>' && av[u.i + 1] != ' '))
		{
			u.flag++;
		}
	}
	return (u.flag);
}

char	*add_space(char *av)
{
	t_util	u;
	char	*str;
	int		original_length;

	util_init(&u);
	original_length = ft_strlen(av);
	u.flag = get_flagcnt(av);
	str = malloc(sizeof(char) * (original_length + (u.flag * 2) + 1));
	if (!str)
		return (NULL);// 메모리 할당 실패 시 NULL 반환
	while (av[++u.i])
	{
		if ((u.i > 1)
			&& (av[u.i] == '<' || av[u.i] == '>')
			&& (av[u.i - 1] != '<' && av[u.i - 1] != '>' && av[u.i - 1] != ' '))
			str[++u.idx] = ' ';
		str[++u.idx] = av[u.i];
		if ((av[u.i] == '<' || av[u.i] == '>')
			&& (av[u.i + 1] != '<' && av[u.i + 1] != '>' && av[u.i + 1] != ' '))
			str[++u.idx] = ' ';
	}
	str[++u.idx] = '\0';
	return (str);
}

void	parsing_in_pipe(char *av, t_node *node, t_env env)
{
	int		len;
	char	*tmp;
	char	**str;
	char	**cmd;

	tmp = add_space(av);
	len = find_flag(tmp, ' ');
	if (ft_find_quotes(tmp, 34) + ft_find_quotes(tmp, 39) == 0)
		str = ft_split(tmp, ' ');
	else
		str = split_space(tmp, len);
	cmd = check_dollar(str, env);
	cmd = check_cmd(cmd);
	cmd = find_fd(cmd, node, env);
	save_in_node(node, cmd, env);
	free(tmp);
	free_str(str);
	free_str(cmd);
}
