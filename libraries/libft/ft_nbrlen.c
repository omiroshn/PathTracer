/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:39:10 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/09 15:33:56 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int num)
{
	int		len;

	if (!num)
		return (1);
	len = 0;
	if (num < 0)
	{
		num *= -1;
		len += 1;
	}
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

size_t	ft_nbrllen(long num)
{
	int		len;

	if (!num)
		return (1);
	len = 0;
	if (num < 0)
	{
		num *= -1;
		len += 1;
	}
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

size_t	ft_nbrulen(unsigned int num)
{
	int		len;

	if (!num)
		return (1);
	len = 0;
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

size_t	ft_nbrullen(unsigned long num)
{
	int		len;

	if (!num)
		return (1);
	len = 0;
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

size_t	ft_nbrflen(double num, long ap)
{
	long	decimalp;

	if (num != num || num == INFINITY)
		return (3);
	decimalp = (long)num;
	return (ft_nbrllen(decimalp) + ap + 1);
}
