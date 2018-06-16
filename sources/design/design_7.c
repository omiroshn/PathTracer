/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_7.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:41:46 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/11 14:20:33 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ctrl_emission_change(t_env *env, t_control *c)
{
	float	tmp;
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	if ((tmp = ft_atof(c->text)) >= 0)
		fig->emission = tmp;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_scene(env);
}

static void	ctrl_p_change(t_env *env, t_control *c)
{
	float	tmp;
	float	*p;
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	p = *(float **)(c->tag + sizeof(float));
	if ((tmp = ft_atof(c->text)) >= 0)
		*p = tmp;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_scene(env);
}

void		init_emission_textbox(t_env *env)
{
	static t_control	*em = NULL;

	if (!em)
	{
		if (!(em = sgl_new_control(TEXTBOX, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		em->name = "obj_emission";
		em->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	em->anchor = &env->sel_obj.pos;
	em->align = (SDL_Rect){102, 130, 66, 20};
	em->border_size = 2;
	em->visible = env->flags.obj_info;
	em->change_callback = ctrl_emission_change;
	em->callback_data = env;
	ft_bzero(em->text, 32);
	sprintf(em->text, "%g", env->sel_obj.obj.emission);
	em->text_it = ft_strlen(em->text);
}

void		init_p1_textbox(t_env *env)
{
	float				*rv;
	static t_control	*p = NULL;

	if (!p)
	{
		if (!(p = sgl_new_control(TEXTBOX, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p->name = "obj_emission";
		p->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	p->font_size = 12;
	p->anchor = &env->sel_obj.pos;
	p->align = (SDL_Rect){32, 153, 60, 15};
	p->visible = env->flags.obj_info;
	p->change_callback = ctrl_p_change;
	p->scroll_callback = ctrl_scroll;
	p->callback_data = env;
	ft_bzero(p->text, 32);
	sprintf(p->text, "%g", env->sel_obj.obj.rad);
	ft_memcpy(p->tag, (float[1]){0.01}, sizeof(float));
	rv = &env->scene.objs_h[env->sel_obj.obj.id].rad;
	ft_memcpy(p->tag + sizeof(float), &rv, sizeof(void *));
	rv = &env->sel_obj.obj.rad;
	ft_memcpy(p->tag + sizeof(float) + sizeof(void *), &rv, sizeof(void *));
	p->text_it = ft_strlen(p->text);
}

void		init_p2_textbox(t_env *env)
{
	float				*rv;
	static t_control	*p = NULL;

	if (!p)
	{
		if (!(p = sgl_new_control(TEXTBOX, &env->win->controls)))
			ft_err_handler("Malloc", "Fails", 0, 1);
		p->name = "obj_emission";
		p->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_IBEAM);
	}
	p->font_size = 12;
	p->anchor = &env->sel_obj.pos;
	p->align = (SDL_Rect){120, 153, 60, 15};
	p->visible = env->flags.obj_info;
	p->change_callback = ctrl_p_change;
	p->scroll_callback = ctrl_scroll;
	p->callback_data = env;
	ft_bzero(p->text, 32);
	sprintf(p->text, "%g", env->sel_obj.obj.rad2);
	ft_memcpy(p->tag, (float[1]){0.01}, sizeof(float));
	rv = &env->scene.objs_h[env->sel_obj.obj.id].rad2;
	ft_memcpy(p->tag + sizeof(float), &rv, sizeof(void *));
	rv = &env->sel_obj.obj.rad2;
	ft_memcpy(p->tag + sizeof(float) + sizeof(void *), &rv, sizeof(void *));
	p->text_it = ft_strlen(p->text);
}
