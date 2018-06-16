/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 18:43:00 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:55:40 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlfnbr(long double num, long ap)
{
	long double	fraction;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num != num)
		return (ft_putstr("nan"));
	else if (num == INFINITY)
		return (ft_putstr("inf"));
	fraction = num - (uintmax_t)num;
	ft_putulnbr((uintmax_t)num);
	if (ap > 0)
		ft_putchar('.');
	fraction += 0.5 * ft_pow(0.1, (double)ap);
	while (ap-- > 0)
	{
		ft_putulnbr((uintmax_t)(fraction *= 10));
		fraction = fraction - (uintmax_t)fraction;
	}
}

void	ft_putenbr_l(double num, long ap)
{
	long	power;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num != num)
		return (ft_putstr("nan"));
	else if (num == INFINITY)
		return (ft_putstr("inf"));
	power = 0;
	while (num >= 10 && ++power)
		num /= 10;
	ft_putfnbr(num, ap);
	ft_putstr("e+0");
	ft_putlnbr(power);
}

void	ft_putenbr_u(double num, long ap)
{
	long	power;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num != num)
		return (ft_putstr("nan"));
	else if (num == INFINITY)
		return (ft_putstr("inf"));
	power = 0;
	while (num >= 10 && ++power)
		num /= 10;
	ft_putfnbr(num, ap);
	ft_putstr("E+0");
	ft_putlnbr(power);
}

void	ft_putelnbr_l(long double num, long ap)
{
	long	power;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num != num)
		return (ft_putstr("nan"));
	else if (num == INFINITY)
		return (ft_putstr("inf"));
	power = 0;
	while (num >= 10 && ++power)
		num /= 10;
	ft_putlfnbr(num, ap);
	ft_putstr("e+0");
	ft_putlnbr(power);
}

void	ft_putelnbr_u(long double num, long ap)
{
	long	power;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num != num)
		return (ft_putstr("nan"));
	else if (num == INFINITY)
		return (ft_putstr("inf"));
	power = 0;
	while (num >= 10 && ++power)
		num /= 10;
	ft_putlfnbr(num, ap);
	ft_putstr("E+0");
	ft_putlnbr(power);
}
