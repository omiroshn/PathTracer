/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_8.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:11:07 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/29 13:52:23 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_material_click(t_env *env, t_control *c)
{
	t_material	tmp;
	t_obj		*fig;

	tmp = *(t_material *)c->tag;
	fig = env->scene.objs_h + env->sel_obj.obj.id;
	fig->material = tmp;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_scene(env);
}

void	init_defuse_material_button(t_env *env)
{
	static t_control	*defuse_m_btn = NULL;

	if (!defuse_m_btn)
	{
		if (!(defuse_m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		defuse_m_btn->name = "defuse_m_btn";
		defuse_m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	defuse_m_btn->font_size = 12;
	defuse_m_btn->anchor = &env->sel_obj.pos;
	defuse_m_btn->align = (SDL_Rect){8, 189, 20, 20};
	defuse_m_btn->visible = env->flags.obj_info;
	defuse_m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	defuse_m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	defuse_m_btn->fore_color = 0x323335;
	defuse_m_btn->click_callback = ctrl_material_click;
	defuse_m_btn->callback_data = env;
	ft_strcpy(defuse_m_btn->text, "D");
	ft_memcpy(defuse_m_btn->tag, (t_material[1]){DIFFUSE}, sizeof(t_material));
}

void	init_emissive_material_button(t_env *env)
{
	static t_control	*emi_m_btn = NULL;

	if (!emi_m_btn)
	{
		if (!(emi_m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		emi_m_btn->name = "emi_m_btn";
		emi_m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	emi_m_btn->font_size = 12;
	emi_m_btn->anchor = &env->sel_obj.pos;
	emi_m_btn->align = (SDL_Rect){30, 189, 20, 20};
	emi_m_btn->visible = env->flags.obj_info;
	emi_m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	emi_m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	emi_m_btn->fore_color = 0x323335;
	emi_m_btn->click_callback = ctrl_material_click;
	emi_m_btn->callback_data = env;
	ft_strcpy(emi_m_btn->text, "E");
	ft_memcpy(emi_m_btn->tag, (t_material[1]){EMISSIVE}, sizeof(t_material));
}

void	init_reflection_material_button(t_env *env)
{
	static t_control	*reflect_m_btn = NULL;

	if (!reflect_m_btn)
	{
		if (!(reflect_m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		reflect_m_btn->name = "reflect_m_btn";
		reflect_m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	reflect_m_btn->font_size = 12;
	reflect_m_btn->anchor = &env->sel_obj.pos;
	reflect_m_btn->align = (SDL_Rect){52, 189, 20, 20};
	reflect_m_btn->visible = env->flags.obj_info;
	reflect_m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	reflect_m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	reflect_m_btn->fore_color = 0x323335;
	reflect_m_btn->click_callback = ctrl_material_click;
	reflect_m_btn->callback_data = env;
	ft_strcpy(reflect_m_btn->text, "R");
	ft_memcpy(reflect_m_btn->tag, (t_material[1]){REFLECT}, sizeof(t_material));
}

void	init_transp_material_button(t_env *env)
{
	static t_control	*transp_m_btn = NULL;

	if (!transp_m_btn)
	{
		if (!(transp_m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		transp_m_btn->name = "transp_m_btn";
		transp_m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	transp_m_btn->font_size = 12;
	transp_m_btn->anchor = &env->sel_obj.pos;
	transp_m_btn->align = (SDL_Rect){74, 189, 20, 20};
	transp_m_btn->visible = env->flags.obj_info;
	transp_m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	transp_m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	transp_m_btn->fore_color = 0x323335;
	transp_m_btn->click_callback = ctrl_material_click;
	transp_m_btn->callback_data = env;
	ft_strcpy(transp_m_btn->text, "T");
	ft_memcpy(transp_m_btn->tag, (t_material[1]){TRANSP}, sizeof(t_material));
}
