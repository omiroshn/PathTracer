/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:55:34 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/09 16:49:39 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(t_wint c)
{
	if (c <= 0x7F)
		ft_putchar_fd(c, 1);
	else if (c <= 0x7FF)
	{
		ft_putchar_fd((c >> 6) + 0xC0, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar_fd((c >> 12) + 0xE0, 1);
		ft_putchar_fd(((c >> 6) & 0x3F) + 0x80, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar_fd((c >> 18) + 0xF0, 1);
		ft_putchar_fd(((c >> 12) & 0x3F) + 0x80, 1);
		ft_putchar_fd(((c >> 6) & 0x3F) + 0x80, 1);
		ft_putchar_fd((c & 0x3F) + 0x80, 1);
	}
}
