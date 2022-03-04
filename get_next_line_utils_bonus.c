/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 15:15:40 by nnakarac          #+#    #+#             */
/*   Updated: 2022/03/04 15:16:00 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
char	*ft_freebuff(t_buffer *p_buff);

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*psrc;
	unsigned char		*pdst;

	if (!dst)
		return (NULL);
	psrc = src;
	pdst = dst;
	while (n-- > 0)
		*pdst++ = *psrc++;
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = 0;
}

char	*ft_freebuff(t_buffer *p_buff)
{
	if (p_buff->buff)
	{
		free(p_buff->buff);
		p_buff->buff = 0;
	}
	p_buff->cur = 0;
	p_buff->len = 0;
	p_buff->next = 0;
	p_buff->last = 0;
	return (0);
}
