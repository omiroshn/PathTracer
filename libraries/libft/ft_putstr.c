/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:59:25 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/08 14:15:21 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char const *s)
{
	if (!s)
		return (ft_putstr("(null)"));
	write(1, s, ft_strlen(s));
}

void	ft_putustr(t_wint const *s)
{
	if (!s)
		return (ft_putstr("(null)"));
	while (*s)
		ft_putchar(*s++);
}

void	ft_putnstr(char const *s, size_t len)
{
	size_t	tmp;

	if (!s)
		return (ft_putstr("(null)"));
	tmp = ft_strlen(s);
	len > tmp ? len = tmp : 0;
	write(1, s, len);
}

void	ft_putunstr(t_wint const *s, size_t len)
{
	intmax_t	tmp;

	if (!s)
		return (ft_putstr("(null)"));
	tmp = ft_strulen(s);
	(intmax_t)len < tmp ? tmp = len : 0;
	while (*s && (tmp -= ft_ucharlen(*s)) >= 0)
		ft_putchar(*s++);
}
