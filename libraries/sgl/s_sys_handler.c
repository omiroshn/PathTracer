/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_sys_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 14:15:00 by pgritsen          #+#    #+#             */
/*   Updated: 2018/01/11 16:29:50 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	s_err_handler(const char *msg, const char *add, int err, t_uchar stop)
{
	if (stop)
	{
		if (!msg)
			exit(err ? err : -1);
		if (err && add)
			ft_printf("{red}%s: {yellow}%s{nc} - {red}%s{nc}\n",
			msg, add, strerror(errno));
		else if (msg && add)
			ft_printf("{red}Error: {yellow}%s : %s{nc}\n", msg, add);
		else
			err ? ft_printf("%s: {red}%s{nc}\n", msg, strerror(err))
				: ft_printf("{red}Error: {yellow}%s{nc}\n", msg);
		exit(err ? err : -1);
	}
	else
	{
		if (err && add)
			ft_printf("{yellow}%s: {cyan}%s{nc} - {red}%s{nc}\n",
			msg, add, strerror(errno));
		else if (msg && add)
			ft_printf("{yellow}Warning: {cyan}%s : %s{nc}\n", msg, add);
		else
			err ? ft_printf("%s: {red}%s{nc}\n", msg, strerror(err))
				: ft_printf("{yellow}Warning: {cyan}%s{nc}\n", msg);
	}
}
