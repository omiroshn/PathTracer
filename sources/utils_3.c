/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 21:42:24 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 10:50:46 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

const char	**get_obj_type(long id, t_uchar clear, long *size)
{
	static char	*types[] = {"\"sphere\"", "\"cylinder\"", "\"cone\"",
		"\"plane\"", "\"ellipsoid\"", "\"parabolid\"", "\"hyperboloid\"",
		"\"disc\"", "\"cube\"", "\"torus\"", "\"mebius\"", "\"julia_fract\"",
		"\"pyramid\"", "\"triangle\"", "\"mandelbulb\"", "\"tetrahedron\"",
		"\"skybox\""};
	static char	*names[] = {"Sphere", "Cylinder", "Cone", "Plane", "Ellipsoid",
		"Parabolid", "Hyperboloid", "Disk", "Cube", "Torus", "Mebius",
		"Julia Fractal", "Pyramid", "Triangle", "Mandelbulb Fractal",
		"Tetrahedron", "Sky Box"};

	if (size)
		*size = sizeof(types) / sizeof(*types);
	if (id >= 0 && id < (long)(sizeof(types) / sizeof(*types)) && clear == 0)
		return ((const char **)&types[id]);
	else if (id >= 0 && id < (long)(sizeof(types) / sizeof(*types)))
		return ((const char **)&names[id]);
	else if (clear == 0)
		return ((const char **)types);
	else
		return ((const char **)names);
}

t_obj		*dlist_to_obj_array(t_dlist *dlst, uint count)
{
	t_dlist	*node;
	t_obj	*arr;
	uint	i;

	arr = malloc((count + 1) * sizeof(t_obj));
	i = 0;
	node = dlst;
	while (node && (node = node->next) != dlst)
		ft_memcpy(&arr[i++], node->content, node->content_size);
	arr[i].type = -1;
	return (arr);
}

void		parse_all_kernels(t_env *env)
{
	ft_printf("OpenCL kernels parsing started... ");
	cl_parse_kernel(&env->cl, &env->cam->kl,
		KERNEL_FOLDER"render.cl", "render_scene");
	cl_reinit_mem(&env->cl, &env->cam->kl.mem,
		sizeof(cl_float3) * env->win->w * env->win->h, 0);
	env->load_progress += 0.1;
	cl_parse_kernel(&env->cl, &env->sel_obj.kl,
		KERNEL_FOLDER"render.cl", "intersect_figure");
	cl_reinit_mem(&env->cl, &env->sel_obj.kl.mem, sizeof(t_obj), 0);
	env->load_progress += 0.1;
	cl_parse_kernel(&env->cl, &env->vis_effect,
		KERNEL_FOLDER"render.cl", "apply_effects");
	env->load_progress += 0.1;
	ft_printf("{green}DONE\n{nc}");
	env->flags.kernels_parsed = 1;
}

void		add_figure(t_scene *scene, t_obj *new)
{
	t_dlist		*dlst;
	uint		i;

	i = -1;
	dlst = scene->objs_l;
	while (++i < scene->objs_c && dlst && (dlst = dlst->next) != scene->objs_l)
		ft_memcpy(dlst->content, &scene->objs_h[i], sizeof(t_obj));
	ft_dlstpush_back(&scene->objs_l, ft_dlstnew(new, sizeof(t_obj)));
	free(scene->objs_h);
	scene->objs_c = ft_dlstsize(scene->objs_l);
	scene->objs_h = dlist_to_obj_array(scene->objs_l, scene->objs_c);
}

double		r0to1(void)
{
	return ((double)rand() / (double)RAND_MAX);
}
