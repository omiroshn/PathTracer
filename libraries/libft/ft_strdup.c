/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 16:31:57 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/03 21:33:37 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strdup(const char *src)
{
	char	*clone;
	size_t	s_l;

	s_l = ft_strlen(src);
	if (!(clone = (char *)ft_memalloc(s_l + 1)))
		return (NULL);
	ft_strncpy(clone, src, s_l + 1);
	if (ft_strlen(clone) != s_l)
		return (NULL);
	return (clone);
}
