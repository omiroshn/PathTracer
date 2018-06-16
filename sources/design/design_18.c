/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_18.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 20:22:44 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 12:14:03 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_add_plane_button(t_env *env)
{
	static t_control	*plane_btn = NULL;

	if (!plane_btn)
	{
		if (!(plane_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		plane_btn->name = "plane_btn";
		plane_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	plane_btn->visible = env->active_tab == ADD_FIGURE;
	plane_btn->font_size = 12;
	plane_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	plane_btn->align = (SDL_Rect){151, 4, 39, 16};
	plane_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	plane_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	plane_btn->fore_color = 0x323335;
	plane_btn->click_callback = ctrl_add_plane;
	plane_btn->callback_data = env;
	ft_strcpy(plane_btn->text, "Plane");
}

void	init_add_elips_button(t_env *env)
{
	static t_control	*elips_btn = NULL;

	if (!elips_btn)
	{
		if (!(elips_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		elips_btn->name = "elips_btn";
		elips_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	elips_btn->visible = env->active_tab == ADD_FIGURE;
	elips_btn->font_size = 12;
	elips_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	elips_btn->align = (SDL_Rect){4, 23, 50, 16};
	elips_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	elips_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	elips_btn->fore_color = 0x323335;
	elips_btn->click_callback = ctrl_add_elips;
	elips_btn->callback_data = env;
	ft_strcpy(elips_btn->text, "Elipsoid");
}

void	init_add_parabol_button(t_env *env)
{
	static t_control	*parabol_btn = NULL;

	if (!parabol_btn)
	{
		if (!(parabol_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		parabol_btn->name = "parabol_btn";
		parabol_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	parabol_btn->visible = env->active_tab == ADD_FIGURE;
	parabol_btn->font_size = 12;
	parabol_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	parabol_btn->align = (SDL_Rect){57, 23, 65, 16};
	parabol_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	parabol_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	parabol_btn->fore_color = 0x323335;
	parabol_btn->click_callback = ctrl_add_parabol;
	parabol_btn->callback_data = env;
	ft_strcpy(parabol_btn->text, "Paraboloid");
}

void	init_add_hyperbol_button(t_env *env)
{
	static t_control	*hyperbol_btn = NULL;

	if (!hyperbol_btn)
	{
		if (!(hyperbol_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		hyperbol_btn->name = "hyperbol_btn";
		hyperbol_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	hyperbol_btn->visible = env->active_tab == ADD_FIGURE;
	hyperbol_btn->font_size = 12;
	hyperbol_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	hyperbol_btn->align = (SDL_Rect){125, 23, 70, 16};
	hyperbol_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	hyperbol_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	hyperbol_btn->fore_color = 0x323335;
	hyperbol_btn->click_callback = ctrl_add_hyperbol;
	hyperbol_btn->callback_data = env;
	ft_strcpy(hyperbol_btn->text, "Hyperboloid");
}

void	init_add_disc_button(t_env *env)
{
	static t_control	*disc_btn = NULL;

	if (!disc_btn)
	{
		if (!(disc_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		disc_btn->name = "disc_btn";
		disc_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	disc_btn->visible = env->active_tab == ADD_FIGURE;
	disc_btn->font_size = 12;
	disc_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	disc_btn->align = (SDL_Rect){198, 23, 30, 16};
	disc_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	disc_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	disc_btn->fore_color = 0x323335;
	disc_btn->click_callback = ctrl_add_disc;
	disc_btn->callback_data = env;
	ft_strcpy(disc_btn->text, "Disc");
}
