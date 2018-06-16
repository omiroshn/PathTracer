/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_19.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:33:14 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 12:16:08 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_add_cube_button(t_env *env)
{
	static t_control	*cube_btn = NULL;

	if (!cube_btn)
	{
		if (!(cube_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		cube_btn->name = "cube_btn";
		cube_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	cube_btn->visible = env->active_tab == ADD_FIGURE;
	cube_btn->font_size = 12;
	cube_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	cube_btn->align = (SDL_Rect){193, 4, 35, 16};
	cube_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	cube_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	cube_btn->fore_color = 0x323335;
	cube_btn->click_callback = ctrl_add_cube;
	cube_btn->callback_data = env;
	ft_strcpy(cube_btn->text, "Cube");
}

void	init_add_torus_button(t_env *env)
{
	static t_control	*torus_btn = NULL;

	if (!torus_btn)
	{
		if (!(torus_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		torus_btn->name = "torus_btn";
		torus_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	torus_btn->visible = env->active_tab == ADD_FIGURE;
	torus_btn->font_size = 12;
	torus_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	torus_btn->align = (SDL_Rect){4, 42, 40, 16};
	torus_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	torus_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	torus_btn->fore_color = 0x323335;
	torus_btn->click_callback = ctrl_add_torus;
	torus_btn->callback_data = env;
	ft_strcpy(torus_btn->text, "Torus");
}

void	init_add_mebius_button(t_env *env)
{
	static t_control	*mebius_btn = NULL;

	if (!mebius_btn)
	{
		if (!(mebius_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		mebius_btn->name = "mebius_btn";
		mebius_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	mebius_btn->visible = env->active_tab == ADD_FIGURE;
	mebius_btn->font_size = 12;
	mebius_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	mebius_btn->align = (SDL_Rect){47, 42, 70, 16};
	mebius_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	mebius_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	mebius_btn->fore_color = 0x323335;
	mebius_btn->click_callback = ctrl_add_mebius;
	mebius_btn->callback_data = env;
	ft_strcpy(mebius_btn->text, "Mebius strip");
}

void	init_add_julia_button(t_env *env)
{
	static t_control	*julia_btn = NULL;

	if (!julia_btn)
	{
		if (!(julia_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		julia_btn->name = "julia_btn";
		julia_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	julia_btn->visible = env->active_tab == ADD_FIGURE;
	julia_btn->font_size = 12;
	julia_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	julia_btn->align = (SDL_Rect){120, 42, 55, 16};
	julia_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	julia_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	julia_btn->fore_color = 0x323335;
	julia_btn->click_callback = ctrl_add_julia;
	julia_btn->callback_data = env;
	ft_strcpy(julia_btn->text, "Julia Set");
}

void	init_add_pyramid_button(t_env *env)
{
	static t_control	*pyramid_btn = NULL;

	if (!pyramid_btn)
	{
		if (!(pyramid_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		pyramid_btn->name = "pyramid_btn";
		pyramid_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	pyramid_btn->visible = env->active_tab == ADD_FIGURE;
	pyramid_btn->font_size = 12;
	pyramid_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	pyramid_btn->align = (SDL_Rect){178, 42, 50, 16};
	pyramid_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	pyramid_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	pyramid_btn->fore_color = 0x323335;
	pyramid_btn->click_callback = ctrl_add_pyramid;
	pyramid_btn->callback_data = env;
	ft_strcpy(pyramid_btn->text, "Pyramid");
}
