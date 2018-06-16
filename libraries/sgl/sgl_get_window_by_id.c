/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_get_window_by_id.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 20:10:37 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/19 16:29:43 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_sgl_window	*sgl_get_window_by_id(t_uint id)
{
	t_wlist			*win;
	t_sgl_window	*tmp;

	if (!g_win_list)
		return (NULL);
	win = g_win_list;
	while ((win = win->next) != g_win_list)
	{
		tmp = (t_sgl_window *)win->content;
		if (tmp->id == id)
			return (tmp);
	}
	return (NULL);
}
