/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:49:55 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:50:25 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	save_stdio(t_stdio *backup)
{
	backup->stdin_backup = dup(STDIN_FILENO);
	backup->stdout_backup = dup(STDOUT_FILENO);
}

void	restore_stdio(t_stdio *backup)
{
	dup2(backup->stdin_backup, STDIN_FILENO);
	dup2(backup->stdout_backup, STDOUT_FILENO);
	close(backup->stdin_backup);
	close(backup->stdout_backup);
}
