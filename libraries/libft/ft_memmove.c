/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:13:33 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/03 23:14:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	unsigned char	*p_d;
	unsigned char	*p_s;
	long long		size;

	p_d = (unsigned char *)destination;
	p_s = (unsigned char *)source;
	size = num;
	if (p_s < p_d)
		while (size-- > 0)
			p_d[size] = p_s[size];
	else
		while (size-- > 0)
			*p_d++ = *p_s++;
	return (destination);
}
