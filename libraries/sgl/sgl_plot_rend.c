/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_plot_rend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cozzmonavt <cozzmonavt@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 18:37:34 by pgritsen          #+#    #+#             */
/*   Updated: 2018/03/10 15:17:34 by cozzmonavt       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

inline void		sgl_plot_rend(t_point p, t_uint color, SDL_Renderer *rend)
{
	SDL_Color	tmp;
	int			dx;
	int			dy;

	SDL_GetRenderDrawColor(rend, &tmp.r, &tmp.g, &tmp.b, &tmp.a);
	SDL_SetRenderDrawColor(rend, color >> 16 & 0xFF, color >> 8 & 0xFF,
									color & 0xFF, color >> 24 & 0xFF);
	dx = ROUND(p.x);
	dy = ROUND(p.y);
	SDL_RenderDrawPoint(rend, dx, dy);
	SDL_SetRenderDrawColor(rend, tmp.r, tmp.g, tmp.b, tmp.a);
}
