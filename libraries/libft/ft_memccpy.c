/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 14:35:56 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/03 20:52:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	while (n--)
	{
		*((unsigned char *)dest++) = *((unsigned char *)src++);
		if (*((unsigned char *)(src - 1)) == (unsigned char)c)
			return (dest);
	}
	return (NULL);
}
