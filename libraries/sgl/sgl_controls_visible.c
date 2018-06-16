/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_controls_visible.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:31:04 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/21 14:34:07 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_controls_visible(t_sgl_window *win, SDL_bool visible, uint group)
{
	t_dlist		*all;
	t_control	*control;

	if (!win->controls)
		return ;
	all = win->controls;
	while ((all = all->next) != win->controls)
	{
		control = (t_control *)all->content;
		control->group == group ? control->visible = visible : 0;
	}
}
