/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 18:56:01 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/04 15:48:59 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	n_l;

	n_l = ft_strlen(needle);
	if (!n_l)
		return ((char *)haystack);
	while (*haystack)
		if (!ft_strncmp(haystack++, needle, n_l))
			return ((char *)(haystack - 1));
	return (NULL);
}
