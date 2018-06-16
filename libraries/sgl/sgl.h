/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 17:31:29 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/12 17:48:15 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Simple Graphics Library
**	Copyright (C) 2018  Pavlo Gritsenko
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef SGL_H
# define SGL_H

# include "libft.h"

# ifdef linux
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_ttf.h>
#  include <SDL2/SDL_image.h>
# else
#  include "SDL.h"
#  include "SDL_ttf.h"
#  include "SDL_image.h"
# endif

# define ICON_PATH "./resources/images/icon.png"
# define FONT_PATH "./resources/fonts/"

typedef struct	s_font
{
	char		*name;
	int			size;
	uint		color;
	TTF_Font	*ttf;
}				t_font;

typedef struct	s_point
{
	double	x;
	double	y;
	double	z;
}				t_point;

typedef struct	s_rotate
{
	double	rx;
	double	ry;
	double	rz;
}				t_rotate;

typedef struct	s_control
{
	enum		e_ctrl_type {
		TEXTBOX,
		BUTTON,
		LABEL
	}			type;
	t_ulong		text_it;
	char		*text;
	t_ulong		tag_it;
	char		*tag;
	const char	*name;
	uint		group;
	uint		font_size;
	uint		active;
	t_uchar		visible;
	SDL_Rect	*anchor;
	SDL_Rect	align;
	SDL_Cursor	*cursor;
	SDL_Surface	*back_img;
	uint		fore_color;
	SDL_Color	back_color;
	SDL_Color	border_color;
	uint		border_size;
	uint		max_length;
	uint		min_length;
	void		(*change_callback)();
	void		(*click_callback)();
	void		(*scroll_callback)();
	void		*callback_data;
}				t_control;

typedef struct	s_window
{
	int				w;
	int				h;
	char			*title;
	uint			id;
	SDL_Window		*p;
	SDL_Renderer	*rend;
	SDL_Texture		*tex;
	SDL_Surface		*surf;
	t_dlist			*controls;
}				t_sgl_window;

void			sgl_init(void);

int				sgl_quit(void (*callback)(), void *data);

void			sgl_plot_rend(t_point p, uint color, SDL_Renderer *rend);

void			sgl_plot_surf(t_point p, uint color, SDL_Surface *surf);

uint			sgl_get_tex(SDL_Texture *tex, int x, int y);

uint			sgl_get_surf(SDL_Surface *surf, int x, int y);

void			sgl_draw_line(t_point a, t_point b, uint color,
								SDL_Renderer *rend);

void			sgl_draw_border(SDL_Renderer *renderer,
									const SDL_Rect *rect, int w);

t_control		*sgl_new_control(enum e_ctrl_type type, t_dlist **container);

t_control		*sgl_find_control(t_sgl_window *win, const char *name);

void			sgl_controls_visible(t_sgl_window *win, SDL_bool visible,
															uint group);

uint			sgl_handle_controls(SDL_Event *event);

void			sgl_textbox_input(t_control *c, SDL_Event *event);

void			sgl_draw_controls(t_sgl_window *win);

void			sgl_draw_textbox(t_control *control, SDL_Renderer *rend);

void			sgl_draw_button(t_control *c, SDL_Renderer *rend);

SDL_Rect		sgl_str_size(t_font *font_data, const char *string);

void			sgl_draw_str(const char *string, t_font *font_data,
								t_point align, SDL_Renderer *rend);

void			sgl_draw_str_center(const char *string, t_font *font_data,
									SDL_Rect align, SDL_Renderer *rend);

t_sgl_window	*sgl_new_window(const char *title, int width,
								int height, uint wm);

void			sgl_win_resize(uint win_id, uint new_width,
								uint new_height);

SDL_Surface		*sgl_imgload(char *path);

t_sgl_window	*sgl_get_window(const char *title);

t_sgl_window	*sgl_get_window_by_id(uint id);

TTF_Font		*sgl_get_font(t_font *font_data);

void			sgl_render_surface(SDL_Renderer *renderer, SDL_Surface *surface,
									t_point align);

void			sgl_vsync(void);

t_point			sgl_atop(const char *src);

int				sgl_check_point(t_point src);

t_point			sgl_rotate_point(t_point p, t_rotate angle);

SDL_Texture		*sgl_surftotex(SDL_Renderer *rend,
								SDL_Surface *surf, SDL_bool free);

#endif
