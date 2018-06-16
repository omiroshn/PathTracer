/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_textbox.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:31:25 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/21 18:56:31 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void		sgl_draw_textbox(t_control *c, SDL_Renderer *rend)
{
	SDL_Rect	t_s;
	SDL_Rect	pos;
	t_point		t_a;
	t_font		font;

	pos = c->anchor ? (SDL_Rect){c->anchor->x + c->align.x,
		c->anchor->y + c->align.y, c->align.w, c->align.h} : c->align;
	font = (t_font){"SourceSans", c->font_size, c->fore_color, 0};
	t_s = sgl_str_size(&font, c->text);
	!c->active ? SDL_SetRenderDrawColor(rend, c->border_color.r,
		c->border_color.g, c->border_color.b, c->border_color.a)
				: SDL_SetRenderDrawColor(rend, 0, 128, 128, 128);
	SDL_RenderFillRect(rend, &pos);
	SDL_SetRenderDrawColor(rend, c->back_color.r, c->back_color.g,
								c->back_color.b, c->back_color.a);
	SDL_RenderFillRect(rend, &(SDL_Rect){pos.x + c->border_size,
		pos.y + c->border_size, pos.w - c->border_size * 2,
		pos.h - c->border_size * 2});
	t_a = (t_point){pos.x + 5 + c->border_size / 2,
									pos.y + c->border_size / 2, 0};
	sgl_draw_str(c->text, &font, t_a, rend);
	if (SDL_GetTicks() / 500 % 2 == 0 && c->active)
		sgl_draw_str("|", &font, (t_point){t_a.x + t_s.w, t_a.y - 2, 0}, rend);
}
