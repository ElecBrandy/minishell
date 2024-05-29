/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:27:02 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 14:14:26 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	check_first_arg
	- check if the first argument is valid
	- if the first argument is not valid, return 1
	- if the first argument is valid, return 0

	valid_log
	- " 12342  241 "	: return 1 (if (ft_arrlen_2d(tmp) > 1))
	- "   3  "			: return 0
	- "  3a  "			: return 1
	- "  3 4  "			: return 1
	- "  3 4a  "		: return 1
	- "  3 4 5  "		: return 1
	- lkj1234214		: return 1	
	- ...
*/

int	check_first_arg(t_node *node, long long *num, int *ll_flag)
{
	char	**tmp;

	tmp = ft_split(node->cmd[1], ' ');
	if (!tmp)
		return (88);
	if (ft_arrlen_2d(tmp) > 1)
	{
		ft_free_2d(tmp);
		return (1);
	}
	else
	{
		*num = ft_strtoll(tmp[0], ll_flag);
		if (is_numeric(tmp[0]) == FALSE)
		{
			ft_free_2d(tmp);
			return (1);
		}
		ft_free_2d(tmp);
		if (*ll_flag == FALSE)
			return (1);
	}
	return (0);
}

int	is_numeric(char *str)
{
	if (str[0] == '-')
		str++;
	while (*str)
	{
		if (ft_isdigit(*str) == FALSE)
			return (FALSE);
		str++;
	}
	return (TRUE);
}
