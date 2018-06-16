/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbinary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:06:55 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/09 20:28:16 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbinary(uintmax_t n)
{
	char	buff[65];
	int		it;

	if (!n)
		return (ft_putchar('0'));
	it = 0;
	while (n)
	{
		buff[it++] = ft_tolower(NUMERIC_ALPHABET[n % 2]);
		n /= 2;
	}
	buff[it] = 0;
	ft_putstr(ft_strrev(buff));
}
