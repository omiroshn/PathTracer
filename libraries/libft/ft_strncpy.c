/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 17:45:04 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/03 21:42:59 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	char	*p_d;

	p_d = dest;
	while (n && *src)
	{
		*p_d++ = *src++;
		n--;
	}
	while (n)
	{
		*p_d++ = 0;
		n--;
	}
	return (dest);
}
