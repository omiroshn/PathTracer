/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 14:57:34 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/10 14:55:25 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ftprintf.h"

inline void		set_types(t_conv *conv, va_list *args, t_basic *types)
{
	types->c = 0;
	conv->size == 1 ? types->c = (char)va_arg(*args, int) : 0;
	conv->size == 2 ? types->c = va_arg(*args, int) : 0;
	conv->size == 3 ? types->i = (t_uc)va_arg(*args, int) : 0;
	conv->size == 4 ? types->i = (char)va_arg(*args, int) : 0;
	conv->size == 5 ? types->i = (t_ush)va_arg(*args, int) : 0;
	conv->size == 6 ? types->i = (short)va_arg(*args, int) : 0;
	conv->size == 7 ? types->i = va_arg(*args, int) : 0;
	conv->size == 8 ? types->p = va_arg(*args, void *) : 0;
	conv->size == 9 ? types->im = va_arg(*args, intmax_t) : 0;
	conv->size == 10 ? types->im = va_arg(*args, size_t) : 0;
	conv->size == 11 ? types->pd = va_arg(*args, ptrdiff_t) : 0;
	conv->size == 12 ? types->f = va_arg(*args, double) : 0;
	conv->size == 13 ? types->f = (float)va_arg(*args, double) : 0;
	conv->size == 14 ? types->lf = va_arg(*args, t_ld) : 0;
}

inline int		arg_zero(t_basic arg, t_conv c)
{
	if (c.size <= 2 && arg.c == 0)
		return (1);
	else if (c.size <= 7 && arg.i == 0)
		return (1);
	else if (c.size <= 8 && arg.p == 0)
		return (1);
	else if (c.size <= 10 && arg.im == 0)
		return (1);
	else if (c.size <= 11 && arg.pd == 0)
		return (1);
	else if (c.size <= 13 && arg.f == 0)
		return (1);
	else if (c.size <= 14 && arg.lf == 0)
		return (1);
	return (0);
}

inline int		arg_negative(t_basic *arg, t_conv *conv)
{
	int		neg;

	neg = 0;
	if (conv->size >= 3 && conv->size <= 7
		&& !conv->uns && arg->i < 0 && (neg = 1))
	{
		arg->ui = ABS(arg->i);
		conv->func = ft_putunbr;
		conv->lf = ft_nbrulen;
	}
	else if (conv->size == 9 && !conv->uns && arg->im < 0 && (neg = 1))
	{
		arg->uim = ABS(arg->im);
		conv->func = ft_putulnbr;
		conv->lf = ft_nbrullen;
	}
	else if (conv->size == 14 && !conv->uns && arg->lf < 0 && (neg = 1))
		arg->lf = ABS(arg->lf);
	else if (conv->size >= 12 && conv->size <= 13
		&& !conv->uns && arg->f < 0 && (neg = 1))
		arg->f = ABS(arg->f);
	return (neg);
}

inline void		ft_printr(t_flags f, t_conv *c, t_basic types, long p)
{
	(f.fill == '0' && f.m_w > 0 && !f.p_f && f.p_s) ? ft_putchar(f.p_s) : 0;
	(f.fill == '0' && f.m_w > 0 && !f.p_f) ? f.p_s = 0 : 0;
	(f.fill == '0' && f.m_w > 0 && !f.p_f && c->prefix && f.prefix
		&& (!arg_zero(types, *c) || c->size == 8)) ? ft_putstr(c->prefix) : 0;
	(f.fill == '0' && f.m_w > 0 && !f.p_f) ? c->prefix = NULL : 0;
	c->size == 8 && c->prefix ? f.fill = ' ' : 0;
	while (f.m_w-- > 0)
		ft_putchar(f.p_f && c->func && c->size != 1 && c->size != 2
			&& c->size != 8 ? ' ' : f.fill);
	(f.p >= 0 && f.p_f && f.p_s && c->func) ? ft_putchar(f.p_s) : 0;
	(f.p >= 0 && f.p_f && f.p_s) ? f.p_s = 0 : 0;
	(f.p >= 0 && f.p_f && c->prefix && f.prefix && (!arg_zero(types, *c)
		|| c->size == 8) && c->func) ? ft_putstr(c->prefix) : 0;
	(f.p >= 0 && f.p_f) ? c->prefix = NULL : 0;
	(f.p_f && f.p <= 0) ? f.fill = 0 : 0;
	while (f.p_f && f.p-- > 0 && c->size >= 2 && (c->size != 8 || f.prefix))
		ft_putchar('0');
	f.p_s ? ft_putchar(f.p_s) : 0;
	(c->prefix && f.prefix && (!arg_zero(types, *c) || c->size == 8))
		? ft_putstr(c->prefix) : 0;
	if (!arg_zero(types, *c) || p > 0 || (c->size == 8 && p)
		|| c->size == 1 || c->size == 2)
		c->func ? FTCALL(c->func, p, types, c->size) : ft_putstr(c->act);
	else if (arg_zero(types, *c) && p <= 0 && f.prefix && c->superp == 'p')
		ft_putchar('0');
}

inline void		ft_printl(t_flags flg, t_conv *c, t_basic types, long p)
{
	flg.p_s && c->func ? ft_putchar(flg.p_s) : 0;
	(c->prefix && flg.prefix && c->func && (!arg_zero(types, *c)
		|| c->size == 8)) ? ft_putstr(c->prefix) : 0;
	while (flg.p-- > 0 && flg.p_f && c->size != 0
			&& c->size >= 3 && c->size != 8)
		ft_putchar('0');
	if (!arg_zero(types, *c) || p > 0 || (c->size == 8 && p)
		|| c->size == 1 || c->size == 2)
		c->func ? FTCALL(c->func, p, types, c->size) : ft_putstr(c->act);
	while (flg.m_w-- > 0)
		ft_putchar(' ');
}
