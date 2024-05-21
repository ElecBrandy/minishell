/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 13:55:41 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/21 14:09:59 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_arrlen_2d(char **array)
{
    int cnt = 0;

    while (array[cnt] != NULL)
    {
        cnt++;
    }
    return (cnt);
}
