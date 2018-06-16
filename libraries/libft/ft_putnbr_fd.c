/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:20:27 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/04 15:45:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	long int	mult;
	long int	n_t;

	mult = 1;
	n_t = n;
	if (n_t < 0)
	{
		ft_putchar_fd('-', fd);
		n_t *= -1;
	}
	if (n_t == 0)
		ft_putchar_fd('0', fd);
	while (n_t / mult != 0)
		mult *= 10;
	while (mult > 1)
	{
		mult /= 10;
		if (mult == 0)
			ft_putchar_fd(n_t + '0', fd);
		else
			ft_putchar_fd(n_t / mult + '0', fd);
		n_t %= mult;
	}
}
