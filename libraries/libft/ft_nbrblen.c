/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrblen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:13:02 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/09 20:30:46 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_nbrblen(unsigned long n)
{
	size_t	len;

	if (!n)
		return (1);
	len = 0;
	while (n)
	{
		n /= 2;
		len++;
	}
	return (len);
}
