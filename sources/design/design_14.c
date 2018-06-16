/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_14.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:02:24 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/01 20:10:50 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ctrl_scale_btn_click(t_env *env, t_control *c)
{
	float	v;
	t_obj	*fig;

	v = *(float *)c->tag;
	fig = env->scene.objs_h + env->sel_obj.obj.id;
	fig->scale += v;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

static void	ctrl_scale_change(t_env *env, t_control *c)
{
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	fig->scale = ft_atof(c->text);
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_scene(env);
}

void		init_scale_textbox(t_env *env)
{
	float				*rv;
	static t_control	*scale = NULL;

	if (!scale)
	{
		if (!(scale = sgl_new_control(TEXTBOX, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		scale->name = "obj_scale";
		scale->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	scale->anchor = &env->sel_obj.pos;
	scale->align = (SDL_Rect){30, 275, 138, 20};
	scale->visible = env->flags.obj_info;
	scale->change_callback = ctrl_scale_change;
	scale->scroll_callback = ctrl_scroll;
	scale->callback_data = env;
	ft_bzero(scale->text, 32);
	sprintf(scale->text, "%g", env->sel_obj.obj.scale);
	scale->text_it = ft_strlen(scale->text);
	ft_memcpy(scale->tag, (float[1]){0.01}, sizeof(float));
	rv = &env->scene.objs_h[env->sel_obj.obj.id].scale;
	ft_memcpy(scale->tag + sizeof(float), &rv, sizeof(void *));
	rv = &env->sel_obj.obj.scale;
	ft_memcpy(scale->tag + sizeof(float) + sizeof(void *), &rv, sizeof(void *));
}

void		init_scale_minus_button(t_env *env)
{
	static t_control	*m_btn = NULL;

	if (!m_btn)
	{
		if (!(m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		m_btn->name = "minus_scale";
		m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	m_btn->font_size = 12;
	m_btn->anchor = &env->sel_obj.pos;
	m_btn->align = (SDL_Rect){8, 275, 20, 20};
	m_btn->visible = env->flags.obj_info;
	m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	m_btn->fore_color = 0x323335;
	m_btn->click_callback = ctrl_scale_btn_click;
	m_btn->callback_data = env;
	ft_strcpy(m_btn->text, "-");
	ft_memcpy(m_btn->tag, (float[1]){-0.1}, sizeof(float));
}

void		init_scale_plus_button(t_env *env)
{
	static t_control	*p_btn = NULL;

	if (!p_btn)
	{
		if (!(p_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p_btn->name = "plus_scale";
		p_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	p_btn->font_size = 12;
	p_btn->anchor = &env->sel_obj.pos;
	p_btn->align = (SDL_Rect){170, 275, 20, 20};
	p_btn->visible = env->flags.obj_info;
	p_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	p_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	p_btn->fore_color = 0x323335;
	p_btn->click_callback = ctrl_scale_btn_click;
	p_btn->callback_data = env;
	ft_strcpy(p_btn->text, "+");
	ft_memcpy(p_btn->tag, (float[1]){0.1}, sizeof(float));
}
