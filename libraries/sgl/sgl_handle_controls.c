/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_handle_controls.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:02:01 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/29 13:47:46 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static uint	mouse_move(t_control *c)
{
	SDL_Rect	p;
	uint		e;
	int			x;
	int			y;

	e = 0;
	p = c->anchor ? (SDL_Rect){c->anchor->x + c->align.x,
		c->anchor->y + c->align.y, c->align.w, c->align.h} : c->align;
	SDL_GetMouseState(&x, &y);
	if (c->cursor &&
		x >= p.x && x < p.x + p.w && y >= p.y && y < p.y + p.h && ++e)
		SDL_SetCursor(c->cursor);
	return (e);
}

static uint	mouse_click_down(t_control *c)
{
	SDL_Rect	p;
	uint		e;
	int			x;
	int			y;

	e = 0;
	p = c->anchor ? (SDL_Rect){c->anchor->x + c->align.x,
		c->anchor->y + c->align.y, c->align.w, c->align.h} : c->align;
	SDL_GetMouseState(&x, &y);
	c->active = 0;
	if (x >= p.x && x < p.x + p.w && y >= p.y && y < p.y + p.h && ++e)
	{
		if (c->type != LABEL)
			c->active = SDL_GetTicks();
		c->click_callback ? c->click_callback(c->callback_data, c) : 0;
	}
	return (e);
}

static void	keydown(t_control *c, SDL_Event *event)
{
	static void	(*handlers[])() = {sgl_textbox_input};

	if ((int)c->type < (int)(sizeof(handlers) / sizeof(*handlers)))
		handlers[c->type](c, event);
}

static uint	mouse_wheel(t_control *c, SDL_Event *event)
{
	SDL_Rect	p;
	uint		e;
	int			x;
	int			y;

	if (c->active == 0)
		return (0);
	e = 0;
	p = c->anchor ? (SDL_Rect){c->anchor->x + c->align.x,
		c->anchor->y + c->align.y, c->align.w, c->align.h} : c->align;
	SDL_GetMouseState(&x, &y);
	if (x >= p.x && x < p.x + p.w && y >= p.y && y < p.y + p.h && ++e)
		c->scroll_callback ? c->scroll_callback(c->callback_data, c,
										event->wheel.y, event->wheel.x) : 0;
	return (e);
}

uint		sgl_handle_controls(SDL_Event *e)
{
	uint			ex;
	t_dlist			*all;
	t_control		*control;
	t_sgl_window	*w;

	if (!e || !(w = sgl_get_window_by_id(e->window.windowID)) || !w->controls)
		return (0);
	ex = 0;
	all = w->controls;
	while ((all = all->next) != w->controls
		&& (control = (t_control *)all->content))
		if (!control->visible && !(control->active = 0))
			continue ;
		else if (e->type == SDL_KEYDOWN && control->active && ++ex)
			keydown(control, e);
		else if (e->type == SDL_MOUSEMOTION)
			ex += mouse_move(control);
		else if (e->type == SDL_MOUSEBUTTONDOWN)
			ex += mouse_click_down(control);
		else if (e->type == SDL_MOUSEBUTTONUP)
			ex += 0;
		else if (e->type == SDL_MOUSEWHEEL)
			ex += mouse_wheel(control, e);
	return (ex);
}
