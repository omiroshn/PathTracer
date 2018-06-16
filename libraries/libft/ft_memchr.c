/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:41:26 by pgritsen          #+#    #+#             */
/*   Updated: 2017/10/27 13:46:59 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *ps;

	ps = (unsigned char *)s - 1;
	while ((++ps) - (unsigned char *)s < (int)n)
		if (*((unsigned char *)ps) == (unsigned char)c)
			return (ps);
	return (NULL);
}
