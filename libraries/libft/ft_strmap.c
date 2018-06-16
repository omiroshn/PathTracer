/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:25:56 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/10 20:57:53 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char		*new;
	int			s_l;
	long long	it;

	if (!s)
		return (NULL);
	else if (!f)
		return ((char *)s);
	s_l = ft_strlen(s);
	if (!(new = (char*)malloc((s_l + 1) * sizeof(char))))
		return (NULL);
	it = -1;
	while (s[++it])
		new[it] = f(s[it]);
	new[it] = 0;
	return (new);
}
