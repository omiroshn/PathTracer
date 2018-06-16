/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 20:06:58 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:58:55 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*new;
	long long	c_l;
	long long	it;

	if (!s)
		return (NULL);
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	c_l = 0;
	while (s[c_l])
		c_l++;
	if (c_l)
		c_l--;
	while (s[c_l] && (s[c_l] == ' ' || s[c_l] == '\n' || s[c_l] == '\t'))
		c_l--;
	if (!(new = (char *)malloc(sizeof(char) * (c_l + 2))))
		return (NULL);
	it = 0;
	while (c_l-- + 1 > 0)
		new[it++] = *s++;
	new[it] = 0;
	return (new);
}
