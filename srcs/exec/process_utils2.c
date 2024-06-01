/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:49:55 by dongwook          #+#    #+#             */
/*   Updated: 2024/06/01 16:19:43 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 표준 입출력을 저장하는 함수
void	save_stdio(t_stdio *backup)
{
	backup->stdin_backup = dup(STDIN_FILENO);
	backup->stdout_backup = dup(STDOUT_FILENO);
}

// 표준 입출력을 복원하는 함수
void	restore_stdio(t_stdio *backup)
{
	dup2(backup->stdin_backup, STDIN_FILENO);
	dup2(backup->stdout_backup, STDOUT_FILENO);
	close(backup->stdin_backup);
	close(backup->stdout_backup);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
