/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_plot_surf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:26:55 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 20:29:51 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

inline void		sgl_plot_surf(t_point p, t_uint color, SDL_Surface *surf)
{
	int	dx;
	int	dy;

	dx = ROUND(p.x);
	dy = ROUND(p.y);
	if (dx >= 0 && dx < surf->w && dy >= 0 && dy < surf->h)
		((t_uint *)surf->pixels)[dy * surf->w + dx] = color;
}
