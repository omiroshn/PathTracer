/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 20:27:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/05 18:40:57 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *src)
{
	const char	*fract;
	long long	tmp;
	int			zeros_count;
	int			sign;
	double		ret;

	sign = 1;
	if (*src == '-' && ++src)
		sign = -1;
	ret = ft_atoll(src);
	fract = src;
	if (!*(fract += ft_skipdigits(src)))
		return (ret * sign);
	tmp = 0;
	if (*fract == '.')
	{
		zeros_count = 0;
		while (fract[zeros_count + 1] == '0')
			zeros_count++;
		tmp = ft_atoll(fract + zeros_count + 1);
		ret += (double)tmp / ft_pow(10, ft_nbrlen(tmp) + zeros_count);
	}
	return (ret * sign);
}
