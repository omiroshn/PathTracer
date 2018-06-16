/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 19:48:18 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/07 18:57:34 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1 && s2)
		return (0);
	else if (!s2 && s1)
		return (0);
	else if (!s1 && !s2)
		return (0);
	while ((*s1 || *s2) && n--)
		if ((unsigned char)*s1++ != (unsigned char)*s2++)
			return (0);
	return (1);
}
