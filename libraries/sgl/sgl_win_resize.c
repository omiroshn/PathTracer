/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_win_resize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:11:53 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 22:04:14 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_win_resize(t_uint win_id, t_uint new_width, t_uint new_height)
{
	t_sgl_window	*win;

	win = sgl_get_window_by_id(win_id);
	win->w = new_width;
	win->h = new_height;
	SDL_DestroyTexture(win->tex);
	SDL_FreeSurface(win->surf);
	!(win->surf = SDL_CreateRGBSurface(0, win->w, win->h, 32, 0, 0, 0, 0))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
	!(win->tex = SDL_CreateTexture(win->rend, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, win->w, win->h))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
}
