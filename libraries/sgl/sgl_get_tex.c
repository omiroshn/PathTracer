/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_get_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:32:21 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/23 20:20:39 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

inline t_uint	sgl_get_tex(SDL_Texture *tex, int x, int y)
{
	t_uint	*pixels;
	t_uint	pixel;
	int		width;
	int		height;

	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
	SDL_LockTexture(tex, NULL, (void **)&pixels, (int *)&pixel);
	if (y >= 0 && y < height && x >= 0 && x < width)
		pixel = pixels[y * width + x];
	else
		pixel = 0x000000;
	SDL_UnlockTexture(tex);
	return (pixel);
}
