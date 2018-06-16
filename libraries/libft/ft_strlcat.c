/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 18:27:34 by pgritsen          #+#    #+#             */
/*   Updated: 2017/10/30 18:23:20 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	register char		*p_dst;
	register const char	*p_src;
	register size_t		out_l;
	register size_t		dst_l;

	p_dst = dst;
	p_src = src;
	out_l = dstsize;
	while (out_l-- && *p_dst)
		p_dst++;
	dst_l = p_dst - dst;
	out_l = dstsize - dst_l;
	if (!out_l)
		return (dst_l + ft_strlen(p_src));
	while (*p_src++)
		if (out_l != 1)
		{
			*p_dst++ = *(p_src - 1);
			out_l--;
		}
	*p_dst = 0;
	return (dst_l + (p_src - src) - 1);
}
