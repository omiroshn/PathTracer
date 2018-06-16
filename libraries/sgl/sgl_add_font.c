/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_add_font.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 16:26:10 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/19 16:26:26 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

TTF_Font	*sgl_add_font(t_font *font_data)
{
	char		file_buff[255];
	t_font		*font;

	if (!(font = ft_memalloc(sizeof(t_font))))
	{
		s_err_handler("SGL", "Malloc fails", 0, 0);
		return (NULL);
	}
	ft_bzero(file_buff, sizeof(file_buff));
	ft_strlcat(file_buff, FONT_PATH, sizeof(file_buff));
	ft_strlcat(file_buff, font_data->name, sizeof(file_buff));
	ft_strlcat(file_buff, ".ttf", sizeof(file_buff));
	if (!(font_data->ttf = TTF_OpenFont(file_buff, font_data->size)))
		return (NULL);
	font->name = ft_strdup(font_data->name);
	font->size = font_data->size;
	font->ttf = font_data->ttf;
	ft_dlstpush(&g_font_list, ft_dlstnew(font, sizeof(t_font)));
	return (font->ttf);
}
