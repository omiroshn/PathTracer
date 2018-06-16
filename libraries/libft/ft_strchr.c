/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/28 17:07:48 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p_s;

	p_s = (char *)s;
	while (*p_s)
		if ((unsigned char)*p_s++ == (unsigned char)c)
			return ((p_s - 1));
	if ((unsigned char)*p_s == (unsigned char)c)
		return (p_s);
	return (NULL);
}
