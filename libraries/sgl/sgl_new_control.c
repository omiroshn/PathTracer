/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_new_control.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skushnir <skushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:45:47 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/22 16:14:57 by skushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_control	*sgl_new_control(enum e_ctrl_type type, t_dlist **container)
{
	t_control	*new;

	if (!(new = ft_memalloc(sizeof(t_control))))
		return (NULL);
	new->text = ft_memalloc(0x8000);
	new->tag = ft_memalloc(0x8000);
	new->type = type;
	new->font_size = 14;
	new->fore_color = 0xFFFFFF;
	new->back_color = (SDL_Color){0x44, 0x44, 0x44, 0xFF};
	new->border_color = (SDL_Color){0x22, 0x22, 0x22, 0xFF};
	new->max_length = 0x7FFF;
	new->visible = 1;
	new->border_size = 1;
	if (container)
		ft_dlstpush(container, ft_dlstnew(new, sizeof(t_control)));
	return (new);
}
