/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_2d_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:19:31 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/19 16:22:08 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_2d_array(char **array)
{
    int cnt = 0;

    while (array[cnt] != NULL)
    {
        cnt++;
    }
    return (cnt);
}
