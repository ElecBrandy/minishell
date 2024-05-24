/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dongeunk <dongeunk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 12:38:30 by dongeunk          #+#    #+#             */
/*   Updated: 2024/02/26 12:56:09 by dongeunk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
t_save	*make_newnode(t_save **head, int fd);
char	*get_next_line2(int fd, char **save, t_save **head, char *buf);
char	*find_next(int fd, char **save, t_save **head);
char	*find_eof(int fd, char **save, t_save **head);

char	*get_next_line(int fd)
{
	static t_save	*head;
	t_save			*node;

	if (fd < 0 || BUFFER_SIZE < 1)
		return ((void *)0);
	if (!head)
		head = make_newnode(&head, fd);
	if (!head)
		return ((void *)0);
	if (!(find_f(head, fd)))
	{
		if (!(make_newnode(&head, fd)))
			return ((void *)0);
	}
	node = find_f(head, fd);
	if (read(fd, node->buf, 0) < 0)
		return (free_n(&head, fd, node->save));
	return (get_next_line2(fd, &(node->save), &head, node->buf));
}

t_save	*make_newnode(t_save **head, int fd)
{
	t_save	*str;
	t_save	*node;

	node = (*head);
	str = (t_save *)malloc(sizeof(t_save));
	if (!str)
		return ((void *)0);
	str->save = free_or_malloc(&(str->save), BUFFER_SIZE + 1);
	if (!(str->save))
	{
		free(str);
		return ((void *)0);
	}
	str->fd = fd;
	str->next = 0;
	if ((*head))
	{
		while (node->next)
			node = node->next;
		node->next = str;
	}
	else
		node = str;
	return (str);
}

char	*get_next_line2(int fd, char **save, t_save **head, char *buf)
{
	t_lis	box;

	box.i = 1;
	while (gnl_strchr_cat(save, '\n', buf) == 0)
	{
		box.read_size = read(fd, buf, BUFFER_SIZE);
		if (box.read_size < 0)
			return (free_n(head, fd, (*save)));
		buf[box.read_size] = '\0';
		if (box.read_size == 0)
			return (find_eof(fd, save, head));
		if (gnl_strlen(*save) + BUFFER_SIZE >= (BUFFER_SIZE * box.i))
		{
			box.i *= 2;
			box.temp = (*save);
			(*save) = free_or_malloc(save, (BUFFER_SIZE * box.i) + 1);
			if (!(*save))
				return (free_n(head, fd, box.temp));
			(*save) = gnl_strchr_cat(save, -1, box.temp);
			free_or_malloc(&box.temp, 0);
		}
		(*save) = gnl_strchr_cat(save, -1, buf);
	}
	return (find_next(fd, save, head));
}

char	*find_eof(int fd, char **save, t_save **head)
{
	t_lis	box;

	box.i = gnl_strlen(*save);
	if (box.i == 0)
		return (free_n(head, fd, (*save)));
	box.line = free_or_malloc(&box.line, box.i + 1);
	if (!box.line)
		return (free_n(head, fd, (*save)));
	box.line = gnl_strchr_cat(&box.line, -1, *save);
	free_n(head, fd, (*save));
	return (box.line);
}

char	*find_next(int fd, char **save, t_save **head)
{
	t_lis		box;

	box.i = -1;
	box.idx = 0;
	while ((*save)[box.idx] != '\n')
		box.idx++;
	box.line = free_or_malloc(&box.line, box.idx + 2);
	if (!box.line)
		return (free_n(head, fd, (*save)));
	while (++box.i < box.idx + 1)
		box.line[box.i] = (*save)[box.i];
	box.line[box.i] = '\0';
	box.temp = (*save);
	box.i = gnl_strlen((*save) + box.idx + 1);
	(*save) = free_or_malloc(save, box.i + 1);
	if (!(*save))
	{
		free_n(head, fd, box.temp);
		return (free_or_malloc(&box.line, 0));
	}
	(*save) = gnl_strchr_cat(save, -1, box.temp + box.idx + 1);
	free_or_malloc(&box.temp, 0);
	return (box.line);
}
