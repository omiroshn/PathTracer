/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_20.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:54:16 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 11:37:29 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_add_mandelbulb_button(t_env *env)
{
	static t_control	*mandelbulb_btn = NULL;

	if (!mandelbulb_btn)
	{
		if (!(mandelbulb_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		mandelbulb_btn->name = "mandelbulb_btn";
		mandelbulb_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	mandelbulb_btn->visible = env->active_tab == ADD_FIGURE;
	mandelbulb_btn->font_size = 12;
	mandelbulb_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	mandelbulb_btn->align = (SDL_Rect){4, 61, 70, 16};
	mandelbulb_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	mandelbulb_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	mandelbulb_btn->fore_color = 0x323335;
	mandelbulb_btn->click_callback = ctrl_add_mandelbulb;
	mandelbulb_btn->callback_data = env;
	ft_strcpy(mandelbulb_btn->text, "Mandelbulb");
}

void	init_add_tetrahedron_button(t_env *env)
{
	static t_control	*tetrahedr_btn = NULL;

	if (!tetrahedr_btn)
	{
		if (!(tetrahedr_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		tetrahedr_btn->name = "tetrahedr_btn";
		tetrahedr_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	tetrahedr_btn->visible = env->active_tab == ADD_FIGURE;
	tetrahedr_btn->font_size = 12;
	tetrahedr_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	tetrahedr_btn->align = (SDL_Rect){77, 61, 70, 16};
	tetrahedr_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	tetrahedr_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	tetrahedr_btn->fore_color = 0x323335;
	tetrahedr_btn->click_callback = ctrl_add_tetrahedron;
	tetrahedr_btn->callback_data = env;
	ft_strcpy(tetrahedr_btn->text, "Tetrahedron");
}
