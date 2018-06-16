/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 21:13:09 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/11 14:19:51 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ctrl_pause_btn_click(t_env *env, t_control *c)
{
	env->flags.pause ^= 1;
	env->flags.pause ? env->flags.move_m = 0 : 0;
	ft_strcpy(c->text, env->flags.pause ? "Resume" : "Pause");
}

void		init_render_pause_button(t_env *env)
{
	static t_control	*p_btn = NULL;

	if (!p_btn)
	{
		if (!(p_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		ft_strcpy(p_btn->text, "Pause");
		p_btn->name = "pause_btn";
	}
	p_btn->anchor = &sgl_find_control(env->win, "actions_p")->align;
	p_btn->font_size = 12;
	p_btn->align = (SDL_Rect){4, 4, 50, 16};
	p_btn->visible = 1;
	p_btn->click_callback = ctrl_pause_btn_click;
	p_btn->callback_data = env;
	p_btn->font_size = 12;
}

static void	ctrl_emission_btn_click(t_env *env, t_control *c)
{
	float	v;
	t_obj	*fig;

	v = *(float *)c->tag;
	fig = env->scene.objs_h + env->sel_obj.obj.id;
	fig->emission += fig->emission + v >= 0 ? v : 0;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

void		init_emission_minus_button(t_env *env)
{
	static t_control	*m_btn = NULL;

	if (!m_btn)
	{
		if (!(m_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		m_btn->name = "minus_emission";
		m_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	m_btn->anchor = &env->sel_obj.pos;
	m_btn->align = (SDL_Rect){80, 130, 20, 20};
	m_btn->visible = env->flags.obj_info;
	m_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	m_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	m_btn->fore_color = 0x323335;
	m_btn->click_callback = ctrl_emission_btn_click;
	m_btn->callback_data = env;
	ft_strcpy(m_btn->text, "-");
	ft_memcpy(m_btn->tag, (float[1]){-0.1}, sizeof(float));
}

void		init_emission_plus_button(t_env *env)
{
	static t_control	*p_btn = NULL;

	if (!p_btn)
	{
		if (!(p_btn = sgl_new_control(BUTTON, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p_btn->name = "minus_emission";
		p_btn->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
	}
	p_btn->anchor = &env->sel_obj.pos;
	p_btn->align = (SDL_Rect){170, 130, 20, 20};
	p_btn->visible = env->flags.obj_info;
	p_btn->border_color = (SDL_Color){0x5e, 0x88, 0x01, 0xff};
	p_btn->back_color = (SDL_Color){0xd1, 0xd1, 0xd3, 0xff};
	p_btn->fore_color = 0x323335;
	p_btn->click_callback = ctrl_emission_btn_click;
	p_btn->callback_data = env;
	ft_strcpy(p_btn->text, "+");
	ft_memcpy(p_btn->tag, (float[1]){0.1}, sizeof(float));
}
