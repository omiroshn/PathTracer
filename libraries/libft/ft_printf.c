/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 20:14:11 by pgritsen          #+#    #+#             */
/*   Updated: 2017/12/25 16:10:55 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ftprintf.h"

const t_conv		g_conv[] = {
	{"s", ft_putnstr, ft_strnlen, 8, NULL, 1, 0},
	{"S", ft_putunstr, ft_strunlen, 8, NULL, 1, 0},
	{"hS", ft_putunstr, ft_strunlen, 8, NULL, 1, 0},
	{"hhS", ft_putunstr, ft_strunlen, 8, NULL, 1, 0},
	{"ls", ft_putunstr, ft_strunlen, 8, NULL, 1, 0},
	{"d", ft_putnbr, ft_nbrlen, 7, NULL, 0, 0},
	{"hd", ft_putnbr, ft_nbrlen, 6, NULL, 0, 0},
	{"hhd", ft_putnbr, ft_nbrlen, 4, NULL, 0, 0},
	{"D", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"hD", ft_putnbr, ft_nbrlen, 7, NULL, 0, 0},
	{"hhD", ft_putnbr, ft_nbrlen, 7, NULL, 0, 0},
	{"lD", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"llD", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"jD", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"zD", ft_putlnbr, ft_nbrllen, 10, NULL, 0, 0},
	{"jd", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"zd", ft_putlnbr, ft_nbrllen, 10, NULL, 0, 0},
	{"ld", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"lld", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"i", ft_putnbr, ft_nbrlen, 7, NULL, 0, 0},
	{"hi", ft_putnbr, ft_nbrlen, 6, NULL, 0, 0},
	{"hhi", ft_putnbr, ft_nbrlen, 4, NULL, 0, 0},
	{"ji", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"zi", ft_putlnbr, ft_nbrllen, 10, NULL, 0, 0},
	{"li", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"lli", ft_putlnbr, ft_nbrllen, 9, NULL, 0, 0},
	{"u", ft_putunbr, ft_nbrulen, 7, NULL, 1, 0},
	{"zu", ft_putulnbr, ft_nbrullen, 10, NULL, 1, 0},
	{"hu", ft_putunbr, ft_nbrulen, 5, NULL, 1, 0},
	{"hhu", ft_putunbr, ft_nbrulen, 3, NULL, 1, 0},
	{"U", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"lU", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"llU", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"jU", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"zU", ft_putulnbr, ft_nbrullen, 10, NULL, 0, 0},
	{"hU", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"hhU", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"ju", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"lu", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"llu", ft_putulnbr, ft_nbrullen, 9, NULL, 1, 0},
	{"c", ft_putchar, ft_ucharlen, 1, NULL, 1, 0},
	{"zc", ft_putchar, ft_ucharlen, 1, NULL, 1, 0},
	{"jc", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"lc", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"llc", ft_putchar, ft_ucharlen, 1, NULL, 1, 0},
	{"hc", ft_putchar, ft_ucharlen, 1, NULL, 1, 0},
	{"hhc", ft_putchar, ft_ucharlen, 1, NULL, 1, 0},
	{"C", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"zC", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"jC", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"lC", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"llC", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"hC", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"hhC", ft_putchar, ft_ucharlen, 2, NULL, 1, 0},
	{"p", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"lp", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"llp", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"hp", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"hhp", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"zp", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"jp", ft_putlhex_l, ft_lhexlen, 8, "0x", 1, 0},
	{"x", ft_puthex_l, ft_hexlen, 7, "0x", 1, 0},
	{"zx", ft_putlhex_l, ft_lhexlen, 10, NULL, 0, 0},
	{"hx", ft_puthex_l, ft_hexlen, 5, "0x", 1, 0},
	{"hhx", ft_puthex_l, ft_hexlen, 3, "0x", 1, 0},
	{"jx", ft_putlhex_l, ft_lhexlen, 9, "0x", 1, 0},
	{"lx", ft_putlhex_l, ft_lhexlen, 9, "0x", 1, 0},
	{"llx", ft_putlhex_l, ft_lhexlen, 9, "0x", 1, 0},
	{"X", ft_puthex_u, ft_hexlen, 7, "0X", 1, 0},
	{"zX", ft_putlhex_u, ft_lhexlen, 10, NULL, 0, 0},
	{"hX", ft_puthex_u, ft_hexlen, 5, "0X", 1, 0},
	{"hhX", ft_puthex_u, ft_hexlen, 3, "0X", 1, 0},
	{"jX", ft_putlhex_u, ft_lhexlen, 9, "0X", 1, 0},
	{"lX", ft_putlhex_u, ft_lhexlen, 9, "0X", 1, 0},
	{"llX", ft_putlhex_u, ft_lhexlen, 9, "0X", 1, 0},
	{"o", ft_putoct, ft_octlen, 7, "0", 1, 'p'},
	{"zo", ft_putloct, ft_loctlen, 10, NULL, 0, 'p'},
	{"ho", ft_putoct, ft_octlen, 5, "0X", 1, 'p'},
	{"hho", ft_putoct, ft_octlen, 3, "0X", 1, 'p'},
	{"jo", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"lo", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"llo", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"O", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"zO", ft_putloct, ft_loctlen, 10, NULL, 0, 'p'},
	{"hO", ft_putoct, ft_octlen, 5, "0X", 1, 'p'},
	{"hhO", ft_putoct, ft_octlen, 5, "0X", 1, 'p'},
	{"jO", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"lO", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"llO", ft_putloct, ft_loctlen, 9, "0", 1, 'p'},
	{"f", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"Lf", ft_putlfnbr, ft_nbrlflen, 14, NULL, 0, 0},
	{"lf", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"llf", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"hf", ft_putfnbr, ft_nbrflen, 13, NULL, 0, 0},
	{"hhf", ft_putfnbr, ft_nbrflen, 13, NULL, 0, 0},
	{"zf", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"jf", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"F", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"LF", ft_putlfnbr, ft_nbrlflen, 14, NULL, 0, 0},
	{"lF", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"llF", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"hF", ft_putfnbr, ft_nbrflen, 13, NULL, 0, 0},
	{"hhF", ft_putfnbr, ft_nbrflen, 13, NULL, 0, 0},
	{"jF", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"zF", ft_putfnbr, ft_nbrflen, 12, NULL, 0, 0},
	{"e", ft_putenbr_l, ft_nbrelen, 12, NULL, 0, 0},
	{"Le", ft_putelnbr_l, ft_nbrellen, 14, NULL, 0, 0},
	{"le", ft_putenbr_l, ft_nbrelen, 12, NULL, 0, 0},
	{"lle", ft_putenbr_l, ft_nbrelen, 12, NULL, 0, 0},
	{"he", ft_putenbr_l, ft_nbrelen, 13, NULL, 0, 0},
	{"hhe", ft_putenbr_l, ft_nbrelen, 13, NULL, 0, 0},
	{"ze", ft_putenbr_l, ft_nbrelen, 12, NULL, 0, 0},
	{"je", ft_putenbr_l, ft_nbrelen, 12, NULL, 0, 0},
	{"E", ft_putenbr_u, ft_nbrelen, 12, NULL, 0, 0},
	{"LE", ft_putelnbr_u, ft_nbrellen, 14, NULL, 0, 0},
	{"lE", ft_putenbr_u, ft_nbrelen, 12, NULL, 0, 0},
	{"llE", ft_putenbr_u, ft_nbrelen, 12, NULL, 0, 0},
	{"hE", ft_putenbr_u, ft_nbrelen, 13, NULL, 0, 0},
	{"hhE", ft_putenbr_u, ft_nbrelen, 13, NULL, 0, 0},
	{"jE", ft_putenbr_u, ft_nbrelen, 12, NULL, 0, 0},
	{"zE", ft_putenbr_u, ft_nbrelen, 12, NULL, 0, 0},
	{"b", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"lb", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"llb", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"hb", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"hhb", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"zb", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"jb", ft_putbinary, ft_nbrblen, 9, "0b", 1, 0},
	{"B", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"lB", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"llB", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"hB", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"hhB", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"zB", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"jB", ft_putbinary, ft_nbrblen, 9, "0B", 1, 0},
	{"r", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"lr", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"llr", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"hr", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"hhr", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"zr", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"jr", ft_putnnp_l, ft_strnnplen, 8, NULL, 1, 0},
	{"R", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{"lR", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{"llR", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{"hR", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{"hhR", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{"zR", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{"jR", ft_putnnp_u, ft_strnnplen, 8, NULL, 1, 0},
	{{0}, 0, 0, 0, 0, 0, 0}
};

const t_color		g_colors[] = {
	{"{nc}", "\033[0m"},
	{"{default}", "\033[39m"},
	{"{black}", "\033[30m"},
	{"{red}", "\033[31m"},
	{"{green}", "\033[32m"},
	{"{yellow}", "\033[33m"},
	{"{blue}", "\033[34m"},
	{"{magenta}", "\033[35m"},
	{"{cyan}", "\033[36m"},
	{"{l_gray}", "\033[37m"},
	{"{d_gray}", "\033[90m"},
	{"{l_red}", "\033[91m"},
	{"{l_green}", "\033[92m"},
	{"{l_yellow}", "\033[93m"},
	{"{l_blue}", "\033[94m"},
	{"{l_magenta}", "\033[95m"},
	{"{l_cyan}", "\033[96m"},
	{"{white}", "\033[97m"},
	{"{b_default}", "\033[49m"},
	{"{b_black}", "\033[40m"},
	{"{b_red}", "\033[41m"},
	{"{b_green}", "\033[42m"},
	{"{b_yellow}", "\033[43m"},
	{"{b_blue}", "\033[44m"},
	{"{b_magenta}", "\033[45m"},
	{"{b_cyan}", "\033[46m"},
	{"{b_l_gray}", "\033[47m"},
	{"{b_d_gray}", "\033[100m"},
	{"{b_l_red}", "\033[101m"},
	{"{b_l_green}", "\033[102m"},
	{"{b_l_yellow}", "\033[103m"},
	{"{b_l_blue}", "\033[104m"},
	{"{b_l_magenta}", "\033[105m"},
	{"{b_l_cyan}", "\033[106m"},
	{"{b_white}", "\033[107m"},
	{NULL, NULL}
};

static int				find_flags(const char *fmt, t_flags *f,
									va_list *args, long tmp)
{
	if (*fmt == '#' && (f->prefix = 1))
		return (1 + find_flags(fmt + 1, f, args, tmp));
	else if (*fmt == '-' && (f->l_j = 1)
		&& (f->fill = ' '))
		return (1 + find_flags(fmt + 1, f, args, tmp));
	else if (*fmt == '0' && !f->l_j && (f->fill = '0'))
		return (1 + find_flags(fmt + 1, f, args, tmp));
	else if (*fmt == '+' && (f->p_s = '+'))
		return (1 + find_flags(fmt + 1, f, args, tmp));
	else if (*fmt == ' ' && f->p_s != '+' && (f->p_s = ' '))
		return (1 + find_flags(fmt + 1, f, args, tmp));
	else if (*fmt == '*' && ((f->m_w = va_arg(*args, int)) + 1))
		return (1 + find_flags(fmt + 1, f, args, tmp));
	else if (ft_isdigit(*fmt) && (f->m_w = ft_atoll((fmt)))
		&& ((tmp = ft_skipdigits(fmt)) + 1))
		return (tmp + find_flags(fmt + tmp, f, args, tmp));
	else if (*fmt == '.' && ft_isdigit(*(fmt + 1)) && (f->p_f = 1)
		&& ((f->p = ft_atoll(fmt + 1)) + 1)
		&& ((tmp = ft_skipdigits(fmt + 1)) + 1) && tmp++)
		return (tmp + find_flags(fmt + tmp, f, args, tmp));
	else if (*fmt == '.' && *(fmt + 1) == '*' && (f->p_f = 1)
		&& ((f->p = va_arg(*args, int)) + 1))
		return (2 + find_flags(fmt + 2, f, args, tmp));
	return ((*fmt == ' ' || *fmt == '0' || (*fmt == '.' && !(f->p = 0)
		&& (f->p_f = 1))) ? 1 + find_flags(fmt + 1, f, args, tmp) : 0);
}

inline static void		parse_flags(t_flags f, t_conv *conv,
									t_basic types, size_t *c_p)
{
	(conv->size == 8 && conv->prefix) ? f.prefix = 1 : 0;
	if (f.m_w < 0 && (f.l_j = 1))
		f.m_w = ft_abs(f.m_w);
	f.p_f && f.p < 0 && f.m_w > 0 ? f.p = f.m_w : 0;
	f.m_w -= conv->lf && (f.p || !arg_zero(types, *conv))
		? FTCALL(conv->lf, f.p, types, conv->size) : 0;
	!conv->func ? f.m_w-- : 0;
	conv->size >= 12 ? f.p_f = 0 : 0;
	f.p -= (conv->lf && f.p_f && f.p > 0 && (conv->size != 8 || f.prefix))
		? FTCALL(conv->lf, f.p, types, conv->size) : 0;
	f.prefix && conv->superp ? f.p-- : 0;
	f.m_w -= (conv->prefix && f.prefix && (!arg_zero(types, *conv)
		|| conv->size == 8)) ? ft_strlen(conv->prefix) : 0;
	*c_p += (conv->prefix && f.prefix && (!arg_zero(types, *conv)
		|| conv->size == 8)) ? ft_strlen(conv->prefix) : 0;
	conv->uns ? f.p_s = 0 : 0;
	f.m_w -= (conv->lf && f.p_f && f.p > 0 && conv->size != 8) ? f.p : 0;
	f.m_w -= f.p_s ? 1 : 0;
	*c_p += f.p_s ? 1 : 0;
	*c_p += f.m_w > 0 ? f.m_w : 0;
	*c_p += (conv->lf && f.p_f && f.p > 0
		&& (conv->size != 8 || f.prefix)) ? f.p : 0;
	f.l_j ? ft_printl(f, conv, types, f.p) : ft_printr(f, conv, types, f.p);
}

/*
**	Flags default values (t_flags f):
**
**		.fw		: 0;
**		.prefix	: 0;
**		.l_j	: 0;
**		.fill	: ' ';
**		.p_s	: 0;
**		.m_w	: 0;
**		.p		: 6;
**		.p_f	: 0;
*/

inline static void		parse_conversions(const char **fmt,
											va_list *args, size_t *c_p)
{
	t_conv	c;
	long	it;
	t_basic	types;
	t_flags	f;

	f = (t_flags){0, 0, 0, ' ', 0, 0, 6, 0};
	it = -1;
	f.fw = find_flags(*fmt, &f, args, it);
	if (!*(*fmt += f.fw))
		return ;
	while (*g_conv[++it].act)
		if (!ft_strncmp(*fmt, g_conv[it].act, ft_strlen(g_conv[it].act)))
			break ;
	c = g_conv[it];
	(!*c.act && !f.p) ? f.p = 1 : 0;
	(!*c.act && !(f.p_s = 0)) ? ft_strncpy(c.act, *fmt, 1) : 0;
	*fmt += ft_strlen(c.act);
	set_types(&c, args, &types);
	arg_negative(&types, &c) ? f.p_s = '-' : 0;
	(c.size == 8 && c.lf && !f.p_f) || c.size == 1 || c.size == 2
		? f.p = FTCALL(c.lf, -1, types, c.size) : 0;
	it = c.lf ? FTCALL(c.lf, f.p, types, c.size) : 1;
	(*c_p) += arg_zero(types, c) && !f.p ? (it = 0) : it;
	(!it && arg_zero(types, c) && f.prefix && c.superp) ? (*c_p)++ : 0;
	parse_flags(f, &c, types, c_p);
}

inline static void		parse_color(const char **fmt, size_t *c_p)
{
	t_color	color;
	long	it;

	it = -1;
	while (g_colors[++it].n)
		if (!ft_strncmp(*fmt, g_colors[it].n, ft_strlen(g_colors[it].n)))
			break ;
	if (!(color = g_colors[it]).n && ++*c_p)
		return (void)(ft_putchar(*(*fmt)++));
	*fmt += ft_strlen(color.n);
	*c_p += ft_strlen(color.v);
	ft_putstr(color.v);
}

int						ft_printf(const char *fmt, ...)
{
	size_t	chars_printed;
	va_list	args;
	int		*tmp;

	chars_printed = 0;
	va_start(args, fmt);
	while (*fmt++)
		if (*(fmt - 1) == '{' && fmt--)
			parse_color(&fmt, &chars_printed);
		else if (*(fmt - 1) == '%' && *fmt == 'n'
			&& (tmp = va_arg(args, int *)) && fmt++)
			*tmp = chars_printed;
		else if (*(fmt - 1) == '%')
			parse_conversions(&fmt, &args, &chars_printed);
		else if (++chars_printed)
			ft_putchar(*(fmt - 1));
	va_end(args);
	return (chars_printed);
}
