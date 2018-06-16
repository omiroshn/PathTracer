/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_textbox_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:43:19 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/29 13:48:00 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void		sgl_textbox_input(t_control *c, SDL_Event *event)
{
	uint	key;
	uint	e;

	e = 0;
	key = event->key.keysym.sym;
	if (key >= SDLK_KP_1 && key <= SDLK_KP_9)
		key = key - SDLK_KP_1 + '0' + 1;
	else if (key == SDLK_KP_0)
		key = '0';
	else if (key == SDLK_KP_PERIOD)
		key = '.';
	else if (key == SDLK_KP_COMMA)
		key = ',';
	if (c->text_it < c->max_length && ft_isprint(key) && ++e)
		c->text[c->text_it++] = key;
	else if (key == SDLK_BACKSPACE && c->text_it > 0 && ++e)
		c->text[--c->text_it] = 0;
	c->change_callback && e ? c->change_callback(c->callback_data, c) : 0;
}
