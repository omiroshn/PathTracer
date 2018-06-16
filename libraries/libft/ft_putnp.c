/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 20:38:51 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:24:29 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	nonprint_helper(char symb, int (*f)(int c))
{
	ft_putchar('\\');
	if (symb == '\b')
		ft_putchar(f('b'));
	else if (symb == '\f')
		ft_putchar(f('f'));
	else if (symb == '\n')
		ft_putchar(f('n'));
	else if (symb == '\r')
		ft_putchar(f('r'));
	else if (symb == '\t')
		ft_putchar(f('t'));
	else
	{
		ft_putchar(f(NUMERIC_ALPHABET[symb / 16]));
		ft_putchar(f(NUMERIC_ALPHABET[symb % 16]));
	}
}

void		ft_putnnp_l(char const *s, size_t len)
{
	size_t	tmpl;

	if (!s)
		return (ft_putstr("(null)"));
	tmpl = ft_strnplen(s);
	len > tmpl ? len = tmpl : 0;
	while (*s && len--)
		if (!ft_isprint(*s))
			nonprint_helper(*s++, &ft_tolower);
		else
			write(1, s++, 1);
}

void		ft_putnnp_u(char const *s, size_t len)
{
	size_t	tmpl;

	if (!s)
		return (ft_putstr("(null)"));
	tmpl = ft_strnplen(s);
	len > tmpl ? len = tmpl : 0;
	while (*s && len--)
		if (!ft_isprint(*s))
			nonprint_helper(*s++, &ft_toupper);
		else
			write(1, s++, 1);
}
