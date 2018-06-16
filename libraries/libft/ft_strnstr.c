/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 20:32:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/04 15:55:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_l;

	n_l = ft_strlen(needle);
	if (!n_l)
		return ((char *)haystack);
	while (*haystack && len-- >= n_l)
		if (!ft_strncmp(haystack++, needle, n_l))
			return ((char *)(haystack - 1));
	return (NULL);
}
