/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:16:50 by dongeunk          #+#    #+#             */
/*   Updated: 2023/10/27 15:58:46 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int			ft_atoi(const char *str);
static int	ft_getint(char *s, int si);

int	ft_atoi(const char *str)
{
	int		si;
	int		ret;
	char	*s;

	s = (char *)str;
	si = 1;
	while ((*s == ' ') || (*s >= 9 && *s <= 13))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			si *= -1;
		s++;
	}
	ret = ft_getint(s, si);
	return (ret * si);
}

static int	ft_getint(char *s, int si)
{
	unsigned long	ret;

	ret = 0;
	while (*s >= '0' && *s <= '9')
	{
		ret = ret * 10 + *(s++) - '0';
		if ((si == 1) && ret > 9223372036854775807)
			return (-1);
		if ((si == -1) && ret > 9223372036854775808U)
			return (0);
	}
	return (ret);
}
