/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:41:40 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/08 11:53:54 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_l(unsigned int n)
{
	char	buff[10];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = ft_tolower(NUMERIC_ALPHABET[n % 16]);
		n /= 16;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}

void	ft_puthex_u(unsigned int n)
{
	char	buff[10];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = ft_toupper(NUMERIC_ALPHABET[n % 16]);
		n /= 16;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}

void	ft_putlhex_l(uintmax_t n)
{
	char	buff[17];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = ft_tolower(NUMERIC_ALPHABET[n % 16]);
		n /= 16;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}

void	ft_putlhex_u(uintmax_t n)
{
	char	buff[17];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = ft_toupper(NUMERIC_ALPHABET[n % 16]);
		n /= 16;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}
