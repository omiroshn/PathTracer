/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/02 11:48:13 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/02 20:29:44 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	*p_s;
	size_t	it;
	char	buff;

	if ((p_s = s) == NULL)
		return (NULL);
	while (*p_s)
		p_s++;
	it = 0;
	while (s + it < p_s--)
	{
		buff = s[it];
		s[it++] = *p_s;
		*p_s = buff;
	}
	return (s);
}
