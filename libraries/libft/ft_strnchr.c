/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 17:08:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/28 17:09:22 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnchr(const char *s, int c, size_t limit)
{
	char	*p_s;

	p_s = (char *)s;
	while (*p_s && limit--)
		if ((unsigned char)*p_s++ == (unsigned char)c)
			return ((p_s - 1));
	if ((unsigned char)*p_s == (unsigned char)c)
		return (p_s);
	return (NULL);
}
