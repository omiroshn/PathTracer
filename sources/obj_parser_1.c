/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 13:43:42 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/11 18:43:54 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vt				*get_vt(t_fig *fig, t_triag *triag)
{
	t_vt	*vt;

	if (fig->vt_c == 0)
		return (NULL);
	vt = ft_memalloc(sizeof(t_vt));
	if (triag->a.y <= 0 || triag->a.y > (int)fig->vt_c
		|| triag->b.y <= 0 || triag->b.y > (int)fig->vt_c
		|| triag->c.y <= 0 || triag->c.y > (int)fig->vt_c)
		ERR("Invalid vt index in facet in obj file");
	vt->vt1 = (cl_float3){.x = fig->vt[triag->a.y - 1].x,
						.y = fig->vt[triag->a.y - 1].y,
						.z = fig->vt[triag->a.y - 1].z};
	vt->vt2 = (cl_float3){.x = fig->vt[triag->b.y - 1].x,
						.y = fig->vt[triag->b.y - 1].y,
						.z = fig->vt[triag->b.y - 1].z};
	vt->vt3 = (cl_float3){.x = fig->vt[triag->c.y - 1].x,
						.y = fig->vt[triag->c.y - 1].y,
						.z = fig->vt[triag->c.y - 1].z};
	return (vt);
}

void				fill_obj_props(t_obj *new, t_fig *fig, t_triag *triag)
{
	if (triag->material_index >= 0)
		new->id_tex = fig->materials[triag->material_index].tex_id;
	if (triag->material_index >= 0)
		new->color = fig->materials[triag->material_index].color;
	if (triag->a.x <= 0 || triag->a.x > (long)fig->v_c
		|| triag->b.x <= 0 || triag->b.x > (long)fig->v_c
		|| triag->c.x <= 0 || triag->c.x > (long)fig->v_c)
		ERR("Invalid v index in facet in obj file");
	new->pos = fig->v[triag->a.x - 1];
	new->dir = fig->v[triag->b.x - 1];
	new->dir2 = fig->v[triag->c.x - 1];
}

void				fill_polygs(t_env *env)
{
	t_obj		*new;
	uint		i;
	uint		id_vt;
	t_vt		*vt;
	t_dlist		*facet;

	i = env->scene.objs_l ?
		((t_obj *)env->scene.objs_l->prev->content)->id + 1 : 0;
	id_vt = env->scene.tex_vt_l ?
		ft_dlstsize(env->scene.tex_vt_l) : 0;
	facet = env->scene.fig->f;
	while (facet && (facet = facet->next) != env->scene.fig->f)
	{
		new = ft_memalloc(sizeof(t_obj));
		new->id = i++;
		new->type = TRIANGLE;
		!new->scale ? new->scale = 1.0F : 0;
		fill_obj_props(new, env->scene.fig, (t_triag *)facet->content);
		vt = get_vt(env->scene.fig, (t_triag *)facet->content);
		ft_dlstpush_back(&env->scene.tex_vt_l, ft_dlstnew(vt, sizeof(t_vt)));
		new->id_vt = id_vt++;
		ft_dlstpush_back(&env->scene.objs_l, ft_dlstnew(new, sizeof(t_obj)));
	}
}

void				allocate_vt(t_env *env)
{
	t_dlist	*vt;
	t_vt	*arr;
	t_vt	*tmp;
	uint	count;
	uint	i;

	count = ft_dlstsize(env->scene.tex_vt_l);
	arr = ft_memalloc(count * sizeof(t_vt));
	i = 0;
	vt = env->scene.tex_vt_l;
	while (vt && (vt = vt->next) != env->scene.tex_vt_l
		&& (tmp = (t_vt *)vt->content))
	{
		arr[i].vt1 = tmp->vt1;
		arr[i].vt2 = tmp->vt2;
		arr[i++].vt3 = tmp->vt3;
	}
	ft_dlstclear(&env->scene.tex_vt_l);
	cl_reinit_mem(&env->cl, &env->scene.texs_vt, sizeof(t_vt) * count, arr);
	free(arr);
}

void				read_obj_scene(int fd, t_env *env, char *mat_folder_name)
{
	t_dlist	*rows;
	int		i;

	env->scene.fig = ft_memalloc(sizeof(t_fig));
	ft_printf("\t{yellow}Obj file{nc} parsing started... ");
	rows = get_content(fd);
	malloc_fig(rows, env->scene.fig);
	parse_obj_figure(rows, rows, env, mat_folder_name);
	ft_dlstclear(&rows);
	fill_polygs(env);
	allocate_vt(env);
	i = -1;
	while (env->scene.fig->materials && env->scene.fig->materials[++i].name)
		free(env->scene.fig->materials[i].name);
	ft_memdel((void **)&env->scene.fig->materials);
	ft_memdel((void **)&env->scene.fig->v);
	ft_memdel((void **)&env->scene.fig->vt);
	ft_memdel((void **)&env->scene.fig->vn);
	ft_dlstclear(&env->scene.fig->f);
	ft_memdel((void **)&env->scene.fig);
	ft_printf("{green}OK{nc}\n");
}
