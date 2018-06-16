/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_get_surf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 20:21:15 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 20:25:06 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

t_uint	sgl_get_surf(SDL_Surface *surf, int x, int y)
{
	t_uint	pixel;

	if (y >= 0 && y < surf->h && x >= 0 && x < surf->w)
		pixel = ((t_uint *)surf->pixels)[y * surf->w + x];
	else
		pixel = 0x000000;
	return (pixel);
}
