/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figure_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 10:30:32 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 11:00:49 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_add_sphere(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = SPHERE;
	new->rad = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, 0, 5}, e));
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_cylinder(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = CYLINDER;
	new->rad = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, -2, 5}, e));
	new->dir = vec_add(e->cam->pos, dir_vector((t_point){0, 2, 5}, e));
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_cone(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = CONE;
	new->rad = 25.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, -2, 5}, e));
	new->dir = vec_add(e->cam->pos, dir_vector((t_point){0, 1, 0}, e));
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_plane(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = PLANE;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, 0, 5}, e));
	new->dir = dir_vector((t_point){0, 0, 1}, e);
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_elips(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = ELLIPSOID;
	new->rad = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, 0, 5}, e));
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}
