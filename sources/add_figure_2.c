/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_figure_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 10:57:49 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 11:25:55 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ctrl_add_parabol(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = PARABOLID;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, -1, 5}, e));
	new->dir = vec_add(e->cam->pos, dir_vector((t_point){0, 1, 5}, e));
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_hyperbol(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = HYPERBOLOID;
	new->rad = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, -1, 5}, e));
	new->dir = vec_add(e->cam->pos, dir_vector((t_point){0, 1, 5}, e));
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_disc(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = DISC;
	new->rad = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, 0, 5}, e));
	new->dir = dir_vector((t_point){0, 0, 1}, e);
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_cube(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = CUBE;
	new->rad = 1.0F;
	new->rad2 = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){-0.5, 0, 5}, e));
	new->dir = vec_add(new->pos, (cl_float3){.x = 0, .y = 0, .z = 1});
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}

void	ctrl_add_torus(t_env *e)
{
	t_obj		*new;

	new = ft_memalloc(sizeof(t_obj));
	new->id = 0;
	if (e->scene.objs_l)
		new->id = ((t_obj *)e->scene.objs_l->prev->content)->id + 1;
	new->type = TORUS;
	new->rad = 0.5F;
	new->rad2 = 1.0F;
	new->color = (cl_float3){.x = r0to1(), .y = r0to1(), .z = r0to1()};
	new->pos = vec_add(e->cam->pos, dir_vector((t_point){0, 0, 5}, e));
	new->dir = dir_vector((t_point){0, 0, 1}, e);
	new->scale = 1.0F;
	add_figure(&e->scene, new);
	if (e->flags.pause)
		ctrl_pause_btn_click(e, sgl_find_control(e->win, "pause_btn"));
	init_scene(e);
}
