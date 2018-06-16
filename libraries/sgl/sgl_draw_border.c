/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_draw_border.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 19:25:50 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/26 19:43:26 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_draw_border(SDL_Renderer *rend, const SDL_Rect *p, int w)
{
	while (w >= 0)
	{
		SDL_RenderDrawRect(rend, &(SDL_Rect){p->x + w, p->y + w,
											p->w - w * 2, p->h - w * 2});
		w--;
	}
}
