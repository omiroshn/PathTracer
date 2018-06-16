/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/25 20:42:56 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/08 20:11:52 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_pow(double num, double power)
{
	double	rnum;
	char	neg;

	if (!power)
		return (1);
	neg = 0;
	if (power < 0 && (power = ABS(power)))
		neg = 1;
	rnum = num;
	while (--power)
		rnum *= num;
	if (neg)
		return (1.0 / rnum);
	return (rnum);
}
