/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 20:49:45 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/29 13:51:53 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ctrl_color_btn_click(t_env *env, t_control *c)
{
	int		v;
	uint	tmp_hex;
	t_obj	*fig;

	v = *(int *)c->tag;
	tmp_hex = TOHEX(TORGB(env->sel_obj.obj.color.x),
		TORGB(env->sel_obj.obj.color.y), TORGB(env->sel_obj.obj.color.z)) + v;
	fig = env->scene.objs_h + env->sel_obj.obj.id;
	fig->color.x = (tmp_hex >> 16 & 0xFF) / 255.0F;
	fig->color.y = (tmp_hex >> 8 & 0xFF) / 255.0F;
	fig->color.z = (tmp_hex & 0xFF) / 255.0F;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

static void	ctrl_color_change(t_env *env, t_control *c)
{
	uint	tmp_hex;
	t_obj	*fig;

	tmp_hex = ft_atol_base(c->text, 16);
	fig = env->scene.objs_h + env->sel_obj.obj.id;
	fig->color.x = (tmp_hex >> 16 & 0xFF) / 255.0F;
	fig->color.y = (tmp_hex >> 8 & 0xFF) / 255.0F;
	fig->color.z = (tmp_hex & 0xFF) / 255.0F;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_scene(env);
}

void		init_color_textbox(t_env *env)
{
	static t_control	*color = NULL;

	if (!color)
	{
		if (!(color = sgl_new_control(TEXTBOX, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		color->name = "obj_color";
		color->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	color->anchor = &env->sel_obj.pos;
	color->align = (SDL_Rect){63, 40, 80, 20};
	color->border_size = 2;
	color->max_length = 6;
	color->visible = env->flags.obj_info;
	color->change_callback = ctrl_color_change;
	color->callback_data = env;
	ft_bzero(color->text, color->max_length);
	sprintf(color->text, "%.0x", TOHEX(TORGB(env->sel_obj.obj.color.x),
			TORGB(env->sel_obj.obj.color.y), TORGB(env->sel_obj.obj.color.z)));
	color->text_it = ft_strlen(color->text);
}

void		init_minus_button(t_env *env)
{
	static t_control	*m_btn = NULL;

	if (!m_btn)
	{
		if (!(m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		m_btn->name = "minus_color";
		m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	m_btn->anchor = &env->sel_obj.pos;
	m_btn->align = (SDL_Rect){147, 40, 20, 20};
	m_btn->visible = env->flags.obj_info;
	m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	m_btn->fore_color = 0x323335;
	m_btn->click_callback = ctrl_color_btn_click;
	m_btn->callback_data = env;
	ft_strcpy(m_btn->text, "-");
	ft_memcpy(m_btn->tag, (int[1]){-2}, sizeof(int));
}

void		init_plus_button(t_env *env)
{
	static t_control	*p_btn = NULL;

	if (!p_btn)
	{
		if (!(p_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p_btn->name = "plus_color";
		p_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	p_btn->anchor = &env->sel_obj.pos;
	p_btn->align = (SDL_Rect){170, 40, 20, 20};
	p_btn->visible = env->flags.obj_info;
	p_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	p_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	p_btn->fore_color = 0x323335;
	p_btn->click_callback = ctrl_color_btn_click;
	p_btn->callback_data = env;
	ft_strcpy(p_btn->text, "+");
	ft_memcpy(p_btn->tag, (int[1]){2}, sizeof(int));
}
