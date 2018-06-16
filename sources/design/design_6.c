/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:17:33 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/01 21:21:01 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ctrl_z_btn_click(t_env *env, t_control *c)
{
	float	v;
	t_obj	*fig;

	v = *(float *)c->tag;
	fig = env->scene.objs_h + env->sel_obj.obj.id;
	if (env->sel_obj.active_pos == CENTER1)
		fig->pos.z += v;
	else if (env->sel_obj.active_pos == CENTER2)
		fig->dir.z += v;
	else if (env->sel_obj.active_pos == CENTER3)
		fig->dir2.z += v;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

static void	ctrl_z_change(t_env *env, t_control *c)
{
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	if (env->sel_obj.active_pos == CENTER1)
		fig->pos.z = ft_atof(c->text);
	else if (env->sel_obj.active_pos == CENTER2)
		fig->dir.z = ft_atof(c->text);
	else if (env->sel_obj.active_pos == CENTER3)
		fig->dir2.z = ft_atof(c->text);
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_scene(env);
}

void		init_z_textbox(t_env *env)
{
	static t_control	*z = NULL;

	if (!z)
	{
		if (!(z = sgl_new_control(TEXTBOX, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		z->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	z->font_size = 12;
	z->anchor = &env->sel_obj.pos;
	z->align = (SDL_Rect){45, 113, 128, 15};
	z->visible = env->flags.obj_info;
	z->change_callback = ctrl_z_change;
	z->scroll_callback = ctrl_z_pos_scroll;
	z->callback_data = env;
	if (env->sel_obj.active_pos == CENTER1)
		sprintf(z->text, "%g", env->sel_obj.obj.pos.z);
	else if (env->sel_obj.active_pos == CENTER2)
		sprintf(z->text, "%g", env->sel_obj.obj.dir.z);
	else if (env->sel_obj.active_pos == CENTER3)
		sprintf(z->text, "%g", env->sel_obj.obj.dir2.z);
	z->text_it = ft_strlen(z->text);
	ft_memcpy(z->tag, (float[1]){0.01}, sizeof(float));
}

void		init_z_minus_button(t_env *env)
{
	static t_control	*m_btn = NULL;

	if (!m_btn)
	{
		if (!(m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		m_btn->name = "minus_z";
		m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	m_btn->font_size = 12;
	m_btn->anchor = &env->sel_obj.pos;
	m_btn->align = (SDL_Rect){28, 113, 15, 15};
	m_btn->visible = env->flags.obj_info;
	m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	m_btn->fore_color = 0x323335;
	m_btn->click_callback = ctrl_z_btn_click;
	m_btn->callback_data = env;
	ft_strcpy(m_btn->text, "-");
	ft_memcpy(m_btn->tag, (float[1]){-0.1}, sizeof(float));
}

void		init_z_plus_button(t_env *env)
{
	static t_control	*p_btn = NULL;

	if (!p_btn)
	{
		if (!(p_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p_btn->name = "plus_z";
		p_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	p_btn->font_size = 12;
	p_btn->anchor = &env->sel_obj.pos;
	p_btn->align = (SDL_Rect){175, 113, 15, 15};
	p_btn->visible = env->flags.obj_info;
	p_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	p_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	p_btn->fore_color = 0x323335;
	p_btn->click_callback = ctrl_z_btn_click;
	p_btn->callback_data = env;
	ft_strcpy(p_btn->text, "+");
	ft_memcpy(p_btn->tag, (float[1]){0.1}, sizeof(float));
}
