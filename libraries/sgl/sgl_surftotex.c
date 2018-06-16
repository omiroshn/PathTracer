/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_surftotex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:16:19 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/17 14:20:19 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

SDL_Texture	*sgl_surftotex(SDL_Renderer *rend, SDL_Surface *surf, SDL_bool free)
{
	SDL_Texture		*ret;

	if (!surf || !rend)
		return (NULL);
	ret = SDL_CreateTextureFromSurface(rend, surf);
	free ? SDL_FreeSurface(surf) : 0;
	return (ret);
}
