/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_17.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 19:30:38 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 12:13:42 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_obj_add_tab_button(t_env *env)
{
	static t_control	*effects_t = NULL;
	static t_tab		f_n = ADD_FIGURE;

	if (!effects_t)
	{
		if (!(effects_t = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		effects_t->name = "obj_add_t";
		effects_t->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	effects_t->font_size = 12;
	effects_t->anchor = &sgl_find_control(env->win, "actions_p")->align;
	effects_t->align = (SDL_Rect){208, 4, 65, 16};
	effects_t->click_callback = ctrl_tabs_click;
	effects_t->callback_data = env;
	ft_strcpy(effects_t->text, "Add figure");
	ft_memcpy(effects_t->tag, &f_n, sizeof(t_tab));
}

void	init_obj_add_panel(t_env *env)
{
	static t_control	*obj_add_p = NULL;

	if (!obj_add_p)
	{
		if (!(obj_add_p = sgl_new_control(LABEL, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		obj_add_p->name = "obj_add_p";
	}
	obj_add_p->visible = env->active_tab == ADD_FIGURE;
	obj_add_p->border_size = 2;
	obj_add_p->align = (SDL_Rect){148, 22, 232, 81};
}

void	init_add_sphere_button(t_env *env)
{
	static t_control	*sphere_btn = NULL;

	if (!sphere_btn)
	{
		if (!(sphere_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		sphere_btn->name = "sphere_btn";
		sphere_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	sphere_btn->visible = env->active_tab == ADD_FIGURE;
	sphere_btn->font_size = 12;
	sphere_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	sphere_btn->align = (SDL_Rect){4, 4, 45, 16};
	sphere_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	sphere_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	sphere_btn->fore_color = 0x323335;
	sphere_btn->click_callback = ctrl_add_sphere;
	sphere_btn->callback_data = env;
	ft_strcpy(sphere_btn->text, "Sphere");
}

void	init_add_cylinder_button(t_env *env)
{
	static t_control	*cylinder_btn = NULL;

	if (!cylinder_btn)
	{
		if (!(cylinder_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		cylinder_btn->name = "cylinder_btn";
		cylinder_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	cylinder_btn->visible = env->active_tab == ADD_FIGURE;
	cylinder_btn->font_size = 12;
	cylinder_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	cylinder_btn->align = (SDL_Rect){52, 4, 54, 16};
	cylinder_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	cylinder_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	cylinder_btn->fore_color = 0x323335;
	cylinder_btn->click_callback = ctrl_add_cylinder;
	cylinder_btn->callback_data = env;
	ft_strcpy(cylinder_btn->text, "Cylinder");
}

void	init_add_cone_button(t_env *env)
{
	static t_control	*cone_btn = NULL;

	if (!cone_btn)
	{
		if (!(cone_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		cone_btn->name = "cone_btn";
		cone_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	cone_btn->visible = env->active_tab == ADD_FIGURE;
	cone_btn->font_size = 12;
	cone_btn->anchor = &sgl_find_control(env->win, "obj_add_p")->align;
	cone_btn->align = (SDL_Rect){109, 4, 39, 16};
	cone_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	cone_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	cone_btn->fore_color = 0x323335;
	cone_btn->click_callback = ctrl_add_cone;
	cone_btn->callback_data = env;
	ft_strcpy(cone_btn->text, "Cone");
}
