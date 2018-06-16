/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strntrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/04 13:42:48 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:58:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strntrim(char const *s, int c)
{
	char		*new;
	long long	c_l;
	long long	it;

	while (*s && (unsigned char)*s == (unsigned char)c)
		s++;
	c_l = 0;
	while (s[c_l])
		c_l++;
	if (c_l)
		c_l--;
	while (s[c_l] && (unsigned char)s[c_l] == (unsigned char)c)
		c_l--;
	if (!(new = (char *)malloc(sizeof(char) * (c_l + 2))))
		return (NULL);
	it = 0;
	while (c_l-- + 1 > 0)
		new[it++] = *s++;
	new[it] = 0;
	return (new);
}
