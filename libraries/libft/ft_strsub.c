/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:53:36 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:58:50 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char		*new;
	long long	it;

	if (s == NULL)
		return (NULL);
	if (!(new = (char *)malloc(len + 1)))
		return (NULL);
	s += start;
	it = 0;
	while (*s && len--)
		new[it++] = *s++;
	new[it] = 0;
	return (new);
}
