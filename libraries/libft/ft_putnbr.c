/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:10:22 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:49:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	long	mult;
	long	n_t;

	mult = 1;
	n_t = n;
	if (n_t < 0)
	{
		ft_putchar('-');
		n_t *= -1;
	}
	if (n_t == 0)
		ft_putchar('0');
	while (n_t / mult != 0)
		mult *= 10;
	while (mult > 1)
	{
		mult /= 10;
		if (mult == 0)
			ft_putchar(n_t + '0');
		else
		{
			ft_putchar(n_t / mult + '0');
			n_t %= mult;
		}
	}
}

void		ft_putlnbr(intmax_t n)
{
	char		buff[21];
	uintmax_t	it;
	uintmax_t	n_t;

	n_t = n;
	if (n < 0)
	{
		ft_putchar('-');
		n_t = -n;
	}
	if (!n)
		ft_putchar('0');
	it = 0;
	while (n_t)
	{
		buff[it++] = n_t % 10 + '0';
		n_t /= 10;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}

void		ft_putfnbr(double num, long ap)
{
	double	fraction;

	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num != num)
		return (ft_putstr("nan"));
	else if (num == INFINITY)
		return (ft_putstr("inf"));
	fraction = num - (long)num;
	ft_putlnbr((long)num);
	if (ap > 0)
		ft_putchar('.');
	fraction += 0.5 * ft_pow(0.1, (double)ap);
	while (ap-- > 0)
	{
		ft_putnbr((long)(fraction *= 10));
		fraction = fraction - (long)fraction;
	}
}

void		ft_putunbr(unsigned int n)
{
	char			buff[11];
	size_t			it;

	if (!n)
		ft_putchar('0');
	it = 0;
	while (n)
	{
		buff[it++] = n % 10 + '0';
		n /= 10;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}

void		ft_putulnbr(uintmax_t n)
{
	char			buff[21];
	uintmax_t		it;

	if (!n)
		ft_putchar('0');
	it = 0;
	while (n)
	{
		buff[it++] = (char)(n % 10 + '0');
		n /= 10;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}
