/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:37:28 by pgritsen          #+#    #+#             */
/*   Updated: 2018/03/06 17:44:14 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_draw_line(t_point a, t_point b, t_uint color, SDL_Renderer *rend)
{
	SDL_Color	tmp;

	SDL_GetRenderDrawColor(rend, &tmp.r, &tmp.g, &tmp.b, &tmp.a);
	SDL_SetRenderDrawColor(rend, color >> 16 & 0xFF, color >> 8 & 0xFF,
									color & 0xFF, color >> 24 & 0xFF);
	SDL_RenderDrawLine(rend, a.x, a.y, b.x, b.y);
	SDL_SetRenderDrawColor(rend, tmp.r, tmp.g, tmp.b, tmp.a);
}
