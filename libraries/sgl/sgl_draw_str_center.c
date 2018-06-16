/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_str_center.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 13:29:43 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/22 13:34:05 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_draw_str_center(const char *string, t_font *font_data,
							SDL_Rect align, SDL_Renderer *rend)
{
	TTF_Font	*font;
	SDL_Color	color;
	SDL_Surface	*text_surf;
	SDL_Texture	*messg;
	SDL_Rect	size;

	if (!(font = sgl_get_font(font_data)))
		return ;
	size = sgl_str_size(font_data, string);
	color = (SDL_Color){.r = font_data->color / 0x10000 % 256,
						.g = font_data->color / 0x100 % 256,
						.b = font_data->color % 256,
						.a = font_data->color / 0x1000000 % 256};
	if (!(text_surf = TTF_RenderUTF8_Blended(font, string, color)))
		return ;
	messg = SDL_CreateTextureFromSurface(rend, text_surf);
	SDL_RenderCopy(rend, messg, NULL,
		&(SDL_Rect){(int)align.x + (align.w - size.w) / 2, (int)align.y,
					text_surf->w, text_surf->h});
	SDL_DestroyTexture(messg);
	SDL_FreeSurface(text_surf);
}
