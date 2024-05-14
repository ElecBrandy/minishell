/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_in_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 10:26:26 by dongeunk          #+#    #+#             */
/*   Updated: 2024/05/12 02:53:04 by dongwook         ###   ########.fr       */
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

void	is_infd(char **str, int *i, t_node *node)
{
	int		idx;

	idx = 0;
	if (!str[(*i) + 1])
		perror("nnnn");
	else
	{
		if (str[(*i) + 1][0] == '<' || str[(*i) + 1][0] == '>')
		{
			perror("not file in");
			return ;
		}
		if (ft_strlen(str[*i]) == 1)
			check_infile(str, i, node);
		else if (ft_strncmp(str[*i], "<<", ft_strlen(str[*i])) == 0)
			heredoc_infile(str, i, node);
		else if (str[*i][1] == '>')
		{
			open(str[(*i) + 1], O_RDWR | O_CREAT | O_APPEND, 0666);
			close(open(str[(*i) + 1], O_RDWR | O_CREAT | O_APPEND, 0666));
			*i += 1;
		}
		else
		{
			perror("notfile error2");
		}
	}
}

char	**find_fd(char **str, t_node *node)
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
			is_infd(str, &i, node);
		else if (ft_strncmp(str[i], ">", 1) == 0)
			is_outfd(str, &i, node);
		else
			cmd[idx++] = ft_strdup(str[i]);
	}
	cmd[idx] = NULL;
	return (cmd);
}

//dongwook
char *add_space(char *av)
{
	t_util u;
	char *str;
	int original_length;
	// printf("원본 av : $%s$\n", av);
	util_init(&u);
	u.i = -1;  // 인덱스를 -1로 초기화

	// 필요한 추가 공간 계산
	original_length = ft_strlen(av);
	while (av[++u.i])
	{
		if ((av[u.i] == '<' || av[u.i] == '>') &&
			(av[u.i + 1] != '<' && av[u.i + 1] != '>' && av[u.i + 1] != ' '))
		{
			u.flag++;
		}
	}
	// 메모리 할당
	str = malloc(sizeof(char) * (original_length + (u.flag * 2) + 1));
	if (!str)
		return NULL;  // 메모리 할당 실패 시 NULL 반환

	u.i = -1;
	u.idx = 0;
	while (av[++u.i])
	{
		if ((u.i > 1) &&
			(av[u.i] == '<' || av[u.i] == '>') &&
			(av[u.i - 1] != '<' && av[u.i - 1] != '>' && av[u.i - 1] != ' '))
			str[u.idx++] = ' ';
		str[u.idx++] = av[u.i];
		if ((av[u.i] == '<' || av[u.i] == '>') &&
			(av[u.i + 1] != '<' && av[u.i + 1] != '>' && av[u.i + 1] != ' '))
			str[u.idx++] = ' ';
	}
	str[u.idx] = '\0';  // 널 종료 문자 추가
	// printf("변환 후str : $%s$\n", str);
	return str;
}



// char	*add_space(char *av)
// {
// 	t_util	u;
// 	char	*str;

// 	printf("av : $%s$\n", av); // dongwook
// 	util_init(&u);
// 	while (av[++u.i])
// 	{
// 		if (av[u.i] == '<' || av[u.i] == '>')
// 		{
// 			if (av[u.i + 1] != '<' && av[u.i + 1] != '>')
// 				if (av[u.i + 1] != ' ')
// 					u.flag++;
// 		}
// 	}
// 	str = malloc(sizeof(char) * ((u.flag * 2) + u.i));
// 	u.i = -1;
// 	u.idx = 0;
// 	while (av[++u.i])
// 	{
// 		if (av[u.i] == '<' || av[u.i] == '>')
// 		{
// 			if (av[u.i - 1] != '<' && av[u.i - 1] != '>')
// 			{
// 				if (av[u.i - 1] != ' ' && u.i > 1)
// 				{
// 					str[u.idx] = ' ';
// 					u.idx++;
// 				}
// 			}
// 		}
// 		str[u.idx] = av[u.i];
// 		u.idx++;
// 		if (av[u.i] == '<' || av[u.i] == '>')
// 		{
// 			if (!((av[u.i + 1] == '<') || (av[u.i + 1] == '>')))
// 			{
// 				if (av[u.i + 1] != ' ')
// 				{
// 					str[u.idx] = ' ';
// 					u.idx++;
// 				}
// 			}
// 		}
// 	}
// 	str[u.idx] = '\0';
// 	return (str);
// }

void	parsing_in_pipe(char *av, t_node *node)
{
	int		len;
	char	*tmp;
	char	**str;
	char	**cmd;

	tmp = add_space(av);
	printf("%s\n", tmp);
	len = find_flag(tmp, ' ');
	if (ft_find_quotes(tmp, 34) + ft_find_quotes(tmp, 39) == 0)
		str = ft_split(tmp, ' ');
	else
		str = split_space(tmp, len);
	cmd = find_fd(str, node);
	cmd = check_cmd(cmd);
	save_in_node(node, cmd);
	free(tmp);
	free_str(str);
	free_str(cmd);
}
