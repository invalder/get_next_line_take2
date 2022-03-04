/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:52:46 by nnakarac          #+#    #+#             */
/*   Updated: 2022/03/04 14:02:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
char	*ft_gnl_buffer(t_buffer *p_buff, int read_cnt);
int		ft_gnl_add_buff(t_buffer *p_buff, int fd);
char	*ft_alloc_buffer(t_buffer *p_buff, size_t buff_size);
char	*ft_gnl_last(t_buffer *p_buff, int read_cnt);

char	*get_next_line(int fd)
{
	static t_buffer	t_buff[100000];
	char			*buff;
	ssize_t			read_cnt;

	// printf("fd: %d\n", fd);
	// printf("BUFFER_SIZE: %d\n", BUFFER_SIZE);
	read_cnt = 1;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 100000 || read(fd, NULL, 0) < 0)
		return (0);
	while (read_cnt)
	{
		buff = ft_alloc_buffer(&t_buff[fd], BUFFER_SIZE);
		// printf("buff: %p\n", buff);
		if (!buff)
			return (NULL);
		read_cnt = ft_gnl_add_buff(&t_buff[fd], fd);
		// printf("read_cnt: %ld\n", read_cnt);
		// printf("buff:\n%s\n", t_buff[fd].buff);
		// printf("len:\n%ld\n", t_buff[fd].len);
		// printf("last:\n%ld\n", t_buff[fd].last);
		// printf("cur:\n%ld\n", t_buff[fd].cur);
		// printf("next:\n%ld\n", t_buff[fd].next);
		buff = ft_gnl_buffer(&t_buff[fd], read_cnt);
		if (buff)
			return (buff);
	}

	// if (!read_cnt)
	// 	return (NULL);
	if (read_cnt < 0)
		return (ft_freebuff(&t_buff[fd]));
	buff = ft_gnl_buffer(&t_buff[fd], read_cnt);
	// printf("ref buff: \n%s\n", buff);
	// if (buff)
	return (buff);
}

char	*ft_gnl_buffer(t_buffer *p_buff, int read_cnt)
{
	size_t	next;
	char	*buff;

	buff = NULL;
	next = p_buff->cur;
	if (p_buff->buff)
	{
		while (p_buff->buff[next] != '\n' && p_buff->buff[next])
			next++;
		if (p_buff->buff[next] == '\n')
		{
			if (next + 1 < p_buff->len)
				ft_alloc_buffer(p_buff, BUFFER_SIZE);
			buff = malloc(sizeof(char) * (next - p_buff->cur + 2));
			if (!buff)
				return (ft_freebuff(p_buff));
			ft_memcpy(buff, &p_buff->buff[p_buff->cur], next - p_buff->cur + 1);
			buff[next - p_buff->cur + 1] = 0;
			p_buff->cur = next + 1;
			p_buff->next = next + 1;
			// printf("next: %ld\n", p_buff->next);
		}
		else if (read_cnt < BUFFER_SIZE) // last buffer
			return (ft_gnl_last(p_buff, read_cnt));
	}
	return (buff);
}

char	*ft_gnl_last(t_buffer *p_buff, int read_cnt)
{
	char	*buff;

	buff = NULL;
	if (read_cnt || (p_buff->cur != p_buff->last))
	{
		buff = malloc(sizeof(char) * (p_buff->last - p_buff->cur + 1));
		if (!buff)
			return (ft_freebuff(p_buff));
		ft_memcpy(buff, &p_buff->buff[p_buff->cur], p_buff->last - p_buff->cur);
		buff[p_buff->last - p_buff->cur] = 0;
	}
		ft_freebuff(p_buff);
	return (buff);
}

int		ft_gnl_add_buff(t_buffer *p_buff, int fd)
{
	ssize_t	read_cnt;
	char	*buff;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	read_cnt = read(fd, buff, BUFFER_SIZE);
	if (read_cnt < 0)
		return (-1);
	if (read_cnt)
	{
		buff[read_cnt] = 0;
		ft_memcpy(p_buff->buff + p_buff->last, buff, read_cnt);
		p_buff->last = p_buff->last + read_cnt;
		p_buff->buff[p_buff->last] = 0;
	}
	free(buff);
	return (read_cnt);
}

char	*ft_alloc_buffer(t_buffer *p_buff, size_t buff_size)
{
	size_t	alloc_size;
	char	*buff;

	alloc_size = buff_size;
	if (p_buff->len == 0)
	{
		p_buff->buff = malloc(sizeof(char) * (alloc_size + 1));
		if (!p_buff->buff)
			return (NULL);
		ft_bzero(p_buff->buff, alloc_size + 1);
		p_buff->len = alloc_size;
	}
	else
	{
		buff = malloc(sizeof(char) *(alloc_size + p_buff->len + 1));
		if (!buff)
			return (NULL);
		ft_memcpy(buff, p_buff->buff, p_buff->len + 1);
		p_buff->len = alloc_size + p_buff->len;
		free(p_buff->buff);
		p_buff->buff = buff;
		p_buff->buff[p_buff->len] = 0;
	}
	return (p_buff->buff);
}
/*
int	main(void)
{
	int	fd;
	char *buff;

	fd = open("./gnlTester/files/41_no_nl", O_RDWR);
	free(get_next_line(fd));
	free(get_next_line(fd));
	close(fd);
	return (0);
}
*/
