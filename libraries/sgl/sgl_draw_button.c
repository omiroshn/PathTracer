/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_button.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 19:37:24 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/26 22:23:05 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

static void		blend_mode(SDL_Renderer *rend)
{
	static SDL_BlendMode	blend = SDL_BLENDMODE_BLEND;
	SDL_BlendMode			tmp;

	SDL_GetRenderDrawBlendMode(rend, &tmp);
	SDL_SetRenderDrawBlendMode(rend, blend);
	blend = tmp;
}

static void		background(t_control *c, SDL_Rect pos, SDL_Renderer *rend)
{
	SDL_Texture	*img;

	!c->active ? SDL_SetRenderDrawColor(rend, c->back_color.r,
		c->back_color.g, c->back_color.b, c->back_color.a)
				: SDL_SetRenderDrawColor(rend, c->back_color.r / 1.5,
		c->back_color.g / 1.5, c->back_color.b / 1.5, c->back_color.a);
	SDL_RenderFillRect(rend, &(SDL_Rect){pos.x + c->border_size,
		pos.y + c->border_size, pos.w - c->border_size * 2,
		pos.h - c->border_size * 2});
	if (c->back_img)
	{
		img = SDL_CreateTextureFromSurface(rend, c->back_img);
		SDL_RenderCopy(rend, img, NULL, &(SDL_Rect){pos.x + c->border_size,
			pos.y + c->border_size, pos.w - c->border_size * 2,
			pos.h - c->border_size * 2});
		SDL_DestroyTexture(img);
	}
}

void			sgl_draw_button(t_control *c, SDL_Renderer *rend)
{
	SDL_Rect	t_s;
	SDL_Rect	pos;
	t_font		font;

	blend_mode(rend);
	pos = c->anchor ? (SDL_Rect){c->anchor->x + c->align.x,
		c->anchor->y + c->align.y, c->align.w, c->align.h} : c->align;
	SDL_GetTicks() - c->active > 100 ? c->active = 0 : 0;
	font = (t_font){"SourceSans", c->font_size, c->fore_color, 0};
	t_s = sgl_str_size(&font, c->text);
	!c->active ? SDL_SetRenderDrawColor(rend, c->border_color.r,
		c->border_color.g, c->border_color.b, c->border_color.a)
				: SDL_SetRenderDrawColor(rend, 0, 128, 128, 128);
	c->active ? pos.y += 1 : 0;
	sgl_draw_border(rend, &pos, c->border_size);
	background(c, pos, rend);
	sgl_draw_str(c->text, &font, (t_point){pos.x + (pos.w - t_s.w) / 2,
									pos.y + (pos.h - t_s.h) / 2, 0}, rend);
	blend_mode(rend);
}
