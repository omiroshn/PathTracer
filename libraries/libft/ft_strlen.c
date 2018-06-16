/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 21:18:40 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/08 14:02:40 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ucharlen(t_wint c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	else if (c <= 0x10FFFF)
		return (4);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	const char	*p_s;

	if (!s)
		return (6);
	p_s = s;
	while (*p_s)
		p_s++;
	return (p_s - s);
}

size_t	ft_strulen(const t_wint *s)
{
	size_t	len;

	if (!s)
		return (6);
	len = 0;
	while (*s)
		len += ft_ucharlen(*s++);
	return (len);
}

size_t	ft_strnlen(const char *s, size_t len)
{
	size_t	tmp;

	if (!s)
		return (6);
	tmp = ft_strlen(s);
	return (len > tmp ? tmp : len);
}

size_t	ft_strunlen(const t_wint *s, size_t len)
{
	size_t		ulen;
	intmax_t	tmp;

	if (!s)
		return (6);
	ulen = 0;
	tmp = ft_strulen(s);
	(intmax_t)len < tmp ? tmp = len : 0;
	while (*s && (tmp -= ft_ucharlen(*s)) >= 0)
		ulen += ft_ucharlen(*s++);
	return (ulen);
}
