/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putoct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 20:05:06 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/06 22:16:12 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putoct(unsigned int n)
{
	char	buff[12];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = NUMERIC_ALPHABET[n % 8];
		n /= 8;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}

void	ft_putloct(unsigned long n)
{
	char	buff[23];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = NUMERIC_ALPHABET[n % 8];
		n /= 8;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}
