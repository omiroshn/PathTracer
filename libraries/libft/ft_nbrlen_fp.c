/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_fp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 18:49:00 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:55:17 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbrlflen(long double num, long ap)
{
	uintmax_t	decimalp;

	if (num != num || num == INFINITY)
		return (3);
	if (num < 0)
		num = -num;
	decimalp = (uintmax_t)num;
	return (ft_nbrullen(decimalp) + ap + 1);
}

size_t		ft_nbrelen(double num, long ap)
{
	long	power;

	if (num != num || num == INFINITY)
		return (3);
	power = 0;
	while (num >= 10 && ++power)
		num /= 10;
	return (ft_nbrflen(num, ap) + ft_nbrllen(power) + 3);
}

size_t		ft_nbrellen(long double num, long ap)
{
	long	power;

	if (num != num || num == INFINITY)
		return (3);
	power = 0;
	while (num >= 10 && ++power)
		num /= 10;
	return (ft_nbrlflen(num, ap) + ft_nbrllen(power) + 3);
}
