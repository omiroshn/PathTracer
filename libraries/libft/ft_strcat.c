/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 17:56:17 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/28 12:58:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	dest_len;
	char	*p_d;

	p_d = dest;
	dest_len = ft_strlen(dest);
	while ((*(p_d++ + dest_len) = *src++))
		;
	return (dest);
}
