/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_16.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 21:20:08 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/01 21:22:27 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_x_pos_scroll(t_env *env, t_control *c, int y)
{
	float	v;
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	v = *(float *)c->tag * (y > 0 ? 1.0F : -1.0F);
	if (env->sel_obj.active_pos == CENTER1)
		fig->pos.x += v;
	else if (env->sel_obj.active_pos == CENTER2)
		fig->dir.x += v;
	else if (env->sel_obj.active_pos == CENTER3)
		fig->dir2.x += v;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

void	ctrl_y_pos_scroll(t_env *env, t_control *c, int y)
{
	float	v;
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	v = *(float *)c->tag * (y > 0 ? 1.0F : -1.0F);
	if (env->sel_obj.active_pos == CENTER1)
		fig->pos.y += v;
	else if (env->sel_obj.active_pos == CENTER2)
		fig->dir.y += v;
	else if (env->sel_obj.active_pos == CENTER3)
		fig->dir2.y += v;
	env->sel_obj.obj = *fig;
	if (env->flags.pause)
		ctrl_pause_btn_click(env, sgl_find_control(env->win, "pause_btn"));
	init_controls(env);
	init_scene(env);
}

void	ctrl_z_pos_scroll(t_env *env, t_control *c, int y)
{
	float	v;
	t_obj	*fig;

	fig = env->scene.objs_h + env->sel_obj.obj.id;
	v = *(float *)c->tag * (y > 0 ? 1.0F : -1.0F);
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
