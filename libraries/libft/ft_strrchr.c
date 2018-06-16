/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:24:23 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/03 22:14:15 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*p_s;

	p_s = (char *)s;
	while (*p_s)
		p_s++;
	while (p_s >= s)
		if ((unsigned char)*p_s-- == (unsigned char)c)
			return (p_s + 1);
	return (NULL);
}
