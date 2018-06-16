/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_new_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:57:02 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/19 16:25:14 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_sgl_window	*sgl_new_window(const char *title, int width,
								int height, t_uint wm)
{
	SDL_Surface		*icon;
	t_sgl_window	*new;

	if ((new = sgl_get_window(title)))
		return (new);
	if (!(new = ft_memalloc(sizeof(t_sgl_window))))
		s_err_handler("SGL", "Couldn't create window.", 0, 1);
	new->w = width;
	new->h = height;
	new->title = ft_strdup(title);
	if (SDL_CreateWindowAndRenderer(width, height, wm, &new->p, &new->rend))
		s_err_handler("SDL", SDL_GetError(), 0, 1);
	!(new->surf = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
	!(new->tex = SDL_CreateTexture(new->rend, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, width, height))
		? s_err_handler("SDL", SDL_GetError(), 0, 1) : 0;
	SDL_SetWindowTitle(new->p, title);
	new->id = SDL_GetWindowID(new->p);
	if (!(icon = IMG_Load(ICON_PATH)))
		s_err_handler(ICON_PATH, "File doesn't exist", 0, 0);
	SDL_SetWindowIcon(new->p, icon);
	SDL_FreeSurface(icon);
	ft_dlstpush(&g_win_list, ft_dlstnew(new, sizeof(t_sgl_window)));
	return (new);
}
