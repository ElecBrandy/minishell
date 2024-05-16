/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongwook <dongwook@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 16:05:38 by dongwook          #+#    #+#             */
/*   Updated: 2024/05/16 16:11:13 by dongwook         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    *ft_realloc(void *ptr, int original_size, int new_size)
{
	void	*new_ptr;
	int		min_size;

	if (new_size == 0)
	{
		ft_free((void **)&ptr); // 새 크기가 0이면 메모리 해제
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size)); // 초기 포인터가 NULL이면 새로 할당
	else
	{
		new_ptr = malloc(new_size); // 새 메모리 할당
		if (new_ptr)
		{
			if (original_size < new_size)
				min_size = original_size; // 원래 크기가 더 작은 경우
			else
				min_size = new_size; // 새 크기가 더 작거나 같은 경우
			ft_memcpy(new_ptr, ptr, min_size); // 데이터 복사
			ft_free((void **)&ptr); // 원래 메모리 해제
		}
		return (new_ptr); // 새 메모리 주소 반환
	}
}
