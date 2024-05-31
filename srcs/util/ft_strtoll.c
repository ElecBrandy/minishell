/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:42:21 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/29 20:24:50 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static long long	get_ll(const char *str, int *flag, int sign);
static int			check_ll(long long result, int digit, int sign, int *flag);

long long	ft_strtoll(const char *str, int *flag)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	*flag = TRUE;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = get_ll(str, flag, sign);
	if (*flag == FALSE)
		return (FALSE);
	return (sign * result);
}

static long long	get_ll(const char *str, int *flag, int sign)
{
	int			i;
	long long	result;
	int			digit;

	i = 0;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i] - '0';
		if (!check_ll(result, digit, sign, flag))
			return (FALSE);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

static int	check_ll(long long result, int digit, int sign, int *flag)
{
	if (sign == 1)
	{
		if (result > MAX_LL / 10
			|| (result == MAX_LL / 10 && digit > MAX_LL % 10))
		{
			errno = ERANGE;
			*flag = FALSE;
			return (FALSE);
		}
	}
	else
	{
		if ((-1 * result < (((-1) * MAX_LL - 1) / 10) \
		|| (-1 * result == ((-1) * MAX_LL - 1) / 10 && -1 * \
			digit < ((-1) * MAX_LL - 1) % 10)))
		{
			errno = ERANGE;
			*flag = FALSE;
			return (FALSE);
		}
	}
	return (TRUE);
}
