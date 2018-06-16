/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipdigits.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 13:30:09 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/01 13:48:30 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_skipdigits(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && ft_isdigit(s[len]))
		len++;
	return (len);
}
