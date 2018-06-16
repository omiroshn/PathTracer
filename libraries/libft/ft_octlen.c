/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_octlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 20:07:03 by pgritsen          #+#    #+#             */
/*   Updated: 2017/11/30 20:10:45 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_octlen(unsigned int n)
{
	size_t	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 8;
		len++;
	}
	return (len);
}

size_t		ft_loctlen(unsigned long n)
{
	size_t	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 8;
		len++;
	}
	return (len);
}
