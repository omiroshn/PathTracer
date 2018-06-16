/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnplen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:39:21 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:26:50 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnplen(const char *s)
{
	size_t	len;

	len = 0;
	--s;
	while (*++s)
		if (*s == '\b' || *s == '\f' || *s == '\n' || *s == '\r' || *s == '\t')
			len += 2;
		else if (!ft_isprint(*s))
			len += 3;
		else
			len++;
	return (len);
}

size_t	ft_strnnplen(const char *s, size_t len)
{
	size_t	tmp;

	if (!s)
		return (6);
	tmp = ft_strnplen(s);
	return (len > tmp ? tmp : len);
}
