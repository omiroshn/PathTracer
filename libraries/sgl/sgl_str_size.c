/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_str_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 14:20:55 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/22 13:33:21 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

SDL_Rect	sgl_str_size(t_font *font_data, const char *string)
{
	SDL_Rect	ret;
	TTF_Font	*font;

	ft_bzero(&ret, sizeof(ret));
	if (!(font = sgl_get_font(font_data)))
		return (ret);
	TTF_SizeText(font, string, &ret.w, &ret.h);
	return (ret);
}
