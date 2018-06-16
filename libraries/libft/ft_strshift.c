/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:49:53 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/24 13:07:28 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strshift(char *str, long offset)
{
	long	i;

	i = 0;
	if (!str)
		return (NULL);
	if (offset < 0)
		offset = ft_strlen(str) - ABS(offset);
	while (str[offset])
		str[i++] = str[offset++];
	while (str[i])
		str[i++] = 0;
	return (str);
}
