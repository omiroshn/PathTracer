/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_get_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:14:19 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/19 16:28:09 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

TTF_Font	*sgl_get_font(t_font *font_data)
{
	t_flist	*f;
	t_font	*font;

	if (!g_font_list)
		return (sgl_add_font(font_data));
	f = g_font_list;
	while ((f = f->next) != g_font_list)
	{
		font = (t_font *)f->content;
		if (!(ft_strcmp(font->name, font_data->name))
			&& font->size == font_data->size)
		{
			font_data->ttf = font->ttf;
			return (font->ttf);
		}
	}
	return (sgl_add_font(font_data));
}
