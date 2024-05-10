/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:37 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/07 21:47:18 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_option(char *str);
static void echo_without_option(t_node *node);
static void echo_with_option(t_node *node);

void ft_echo(t_node *node)
{
    size_t	i;
    int		n_flag;

	n_flag = FALSE;
	i = 1;

	if (node->cmd[1] == NULL) // "echo" 만 존재하는 경우
		printf("\n");
	else // 인자가 존재하는 경우
	{
		if (is_option(node->cmd[1])) // "-n" 옵션이 있는 경우
		{
			echo_with_option(node);
		}
		else // "-n" 옵션이 없는 경우
		{
			echo_without_option(node);
			printf("\n");
		}
	}
	exit(0); // Error?
}

static void echo_without_option(t_node *node)
{
	size_t i;

	i = 1;
	while (node->cmd[i])
	{
		printf("%s", node->cmd[i]);
		if (node->cmd[i + 1])
			printf(" ");
		i++;
	}
}

static void echo_with_option(t_node *node)
{
	size_t i;

	i = 2;
	while (node->cmd[i] && is_option(node->cmd[i])) // 옵션 넘기기
	{
		i++;
	}	
	while (node->cmd[i]) // 옵션 이후 출력
	{
		printf("%s", node->cmd[i]);
		if (node->cmd[i + 1])
			printf(" ");
		i++;
	}
}

static int is_option(char *cmd)
{
	size_t i;

    if (cmd[0] != '-' || cmd[1] != 'n') // '-'로 시작하지 않거나 두 번째 문자가 'n'이 아닌 경우
        return (FALSE);
	i = 2;
    while (cmd[i])
	{
        if (cmd[i] != 'n') // 'n' 이외의 다른 문자가 있다면
            return FALSE;
        i++;
    }
    return TRUE;
}

