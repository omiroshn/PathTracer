/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_controls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:08:34 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/26 20:03:14 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_draw_controls(t_sgl_window *win)
{
	t_dlist		*all;
	t_control	*control;
	static void	(*draw_func[])() = {sgl_draw_textbox, sgl_draw_button,
		sgl_draw_button};

	if (!win->controls)
		return ;
	all = win->controls;
	while ((all = all->prev) != win->controls)
	{
		control = (t_control *)all->content;
		control->visible ? draw_func[control->type](control, win->rend) : 0;
	}
}
