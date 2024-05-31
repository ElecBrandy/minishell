/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 14:27:16 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/31 16:49:31 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*
	Rule of env KEY
	1. first character must be an alphabet or an underscore
	2. the rest of characters must be an alphabet, an underscore, or a digit
*/

int	is_key(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (FALSE);
	if (ft_isdigit(key[0]))
		return (FALSE);
	if (!ft_isalnum(key[0]) && key[0] != '_')
		return (FALSE);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_' && key[i] != '=')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*
	Rule of env VALUE
	1. NULL is valid
	2. control characters are invalid
	3. only printable characters are valid(in minishell)
*/
int	is_value(char *value)
{
	int	i;

	i = 0;
	if (value == NULL || *value == '\0')
	{
		return (TRUE);
	}
	while (value[i])
	{
		if (value[i] < 32 || value[i] == 127)
		{
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
