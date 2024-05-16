/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:21:50 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 20:05:56 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_env(t_data *data)
{
	int		i;
	char	**env;

	env = env_to_arr(data);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	exit(0); // Error?
}
