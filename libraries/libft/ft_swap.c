/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/06 15:49:25 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/08 21:16:47 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap_c(char *a, char *b)
{
	char	buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

void	ft_swap_si(short int *a, short int *b)
{
	short int	buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

void	ft_swap_i(int *a, int *b)
{
	int		buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

void	ft_swap_l(long *a, long *b)
{
	long	buff;

	buff = *a;
	*a = *b;
	*b = buff;
}

void	ft_swap_f(double *a, double *b)
{
	double	buff;

	buff = *a;
	*a = *b;
	*b = buff;
}
