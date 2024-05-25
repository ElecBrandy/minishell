/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoll.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 15:42:21 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/25 16:46:47 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long long get_longlong(const char *str, int *signal, int sign);
static int check_longlong(long long result, int digit, int sign, int *signal);

long long	ft_strtoll(const char *str, int *signal)
{
	long long result = 0;
	int sign = 1;
	*signal = TRUE;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = get_longlong(str, signal, sign);
	if (*signal == FALSE)
		return (FALSE);
	return (sign * result);
}

static long long get_longlong(const char *str, int *signal, int sign)
{
	int i = 0;
	long long result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		int digit = str[i] - '0';
		if (!check_longlong(result, digit, sign, signal))
			return (FALSE);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}

static int check_longlong(long long result, int digit, int sign, int *signal)
{
	if (sign == 1) // Check for overflow
	{
		if (result > MAX_LONGLONG / 10 || (result == MAX_LONGLONG / 10 && digit > MAX_LONGLONG % 10))
		{
			errno = ERANGE;
			*signal = FALSE;
			return FALSE;
		}
	}
	else // Check for underflow
	{
		if (-result < MIN_LONGLONG / 10 || (-result == MIN_LONGLONG / 10 && -digit < MIN_LONGLONG % 10))
		{
			errno = ERANGE;
			*signal = FALSE;
			return FALSE;
		}
	}
	return TRUE;
}
