/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 16:17:56 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/26 16:53:48 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

// int is_justcmd(char *str)
// {
// 	int	len;

// 	len = ft_strlen(str);
// 	if (len > 1)
// 	{
// 		if (str[0] == '/')
// 			return (FALSE); // relative path or absolute path
// 	}
// 	if (len > 2)
// 	{
// 		if (str[0] == '.' && str[1] == '/')
// 			return (FALSE); // relative path or absolute path
// 	}
// 	if (len > 3)
// 	{
// 		if (str[0] == '.' && str[1] == '.' && str[2] == '/')
// 			return (FALSE); // relative path or absolute path
// 	}
// 	return (TRUE); // just command
// }
