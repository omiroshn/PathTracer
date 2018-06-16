/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_find_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:08:17 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/26 20:05:52 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_control	*sgl_find_control(t_sgl_window *win, const char *name)
{
	t_dlist		*all;
	t_control	*control;

	if (!win->controls)
		return (NULL);
	all = win->controls;
	while ((all = all->next) != win->controls)
	{
		control = (t_control *)all->content;
		if (control->name && !ft_strcmp(control->name, name))
			return (control);
	}
	return (NULL);
}
