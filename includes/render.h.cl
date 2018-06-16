/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:16:51 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/12 19:14:17 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# define BOUNCE_DEPTH 4

# define JULIA_MAX_IT 8
__constant float EPSILON = 0.00003F;
__constant float ESCAPE_THRESHOLD = 1e1F;

# define SKYBOX_RADIUS 600

# define OIL_LEVELS 30
# define OIL_FILTER_OFFSET 4

typedef unsigned char	t_uchar;
typedef unsigned long	t_ulong;
typedef unsigned short	t_ushort;

typedef float3	cl_float3;

# include "structures.h"

typedef struct	s_obj_data
{
	t_obj	obj;
	float	closest_t;
	float	longest_t;
}				t_obj_data;

/*---------------------------------UTILITIES----------------------------------*/

int			SolveP3(float *x,float a,float b,float c);
int   		SolveP4(float *x, float a, float b, float c, float d);

float		lerp(float v0, float v1, float t);
float3		lerp3(float3 v0, float3 v1, float t);
float3		get_obj_color(float3 NL, float3 P, t_obj obj,
							__global int2 *textures_info, __global uint *textures,
							__global t_vt *all_vt);
float3		reflect_ray(float3 R, float3 N);
float		deg_to_rad(float deg);
float4		qMult(const float4 Q1, const float4 Q2);
float4		qsqr(const float4 Q);
float		rgb2luma(float3 rgb);
float3		hex_to_rgb(uint hex);
float3		avg_color(float3 arr[], uint num);
float3		canvas_to_viewport(float x, float y, t_viewport vwp);
float3		rotate_point(float3 rot, float3 D);
float3		calc_normal(float3 P, float3 D, t_obj obj);
float2		calc_uv(float3 N, float3 P, t_obj obj, __global t_vt *all_vt);
float		fix_limits(float3 O, float3 D, float3 Va, t_obj obj, float ints);

/*-------------------------------INTERSECTIONS--------------------------------*/

float2		intersect_ray_plane(float3 O, float3 D, t_obj obj);
float2		intersect_ray_cylinder(float3 O, float3 D, t_obj *obj);
float2		intersect_ray_cone(float3 O, float3 D, t_obj *obj);
float2		intersect_ray_sphere(float3 O, float3 D, t_obj obj);
float2		intersect_ray_ellipsoid(float3 O, float3 D, t_obj obj);
float2		intersect_ray_parabolid(float3 O, float3 D, t_obj obj);
float2		intersect_ray_hyperboloid(float3 O, float3 D, t_obj obj);
float2		intersect_ray_disc(float3 O, float3 D, t_obj obj);
float2		intersect_ray_cube(float3 O, float3 D, t_obj obj);
float2		intersect_ray_piramid(float3 O, float3 D, t_obj obj);
float2		intersect_ray_tetrahedron(float3 O, float3 D, t_obj obj);
float2		intersect_ray_julia(float3 O, float3 D, t_obj *obj);
float		IterateIntersect(float3 z0);
float2		intersect_ray_mandelbulb(float3 O, float3 D, t_obj *obj);
float2		intersect_ray_mebius(float3 O, float3 D, t_obj obj);
float2		choose_intersection(float3 O, float3 D, t_obj *obj, int type);
t_obj_data	closest_intersection(float3 O, float3 D, __global t_obj *objs);

/*--------------------------------PATHTRACING---------------------------------*/

float3		randomHemisphereDirection(float3 NL, uint *seed0, uint *seed1);
float		fresnelReflectAmount(float n1, float n2, float3 NL, float3 D, float spec);
float3		reflectHemisphereDirection(t_obj *obj, bool *phong, float3 NL, float3 D, uint *seed0, uint *seed1);
float3		transparentDirection(t_obj *obj, bool *phong, float3 NL, float3 D, uint *seed0, uint *seed1);
float3		glassRefractionDirection(t_obj *obj, float3 NL, float3 N, float3 *O, float3 D, float3 P, float3 *mask, uint *seed0, uint *seed1);

float3		trace_ray(float3 O, float3 D, __global t_obj *objs,
						uint *seed0, uint *seed1, float ambient_light,
						__global int2 *textures_info, __global uint *textures,
						__global t_vt *all_vt);

/*----------------------------------KERNELS-----------------------------------*/

__kernel void
render_scene(
	__global	float3		*colors,
				float3		O,
				float3		rot,
				t_viewport	vwp,
	__global	t_obj		*objs,
				uint		random_seed,
				uint		total_samples,
				float		ambient_light,
	__global	uint		*output,
	__global	uint		*textures,
	__global	int2		*textures_info,
	__global	t_vt		*all_vt,
				char		smooth);

__kernel void
intersect_figure(
	__global	t_obj		*obj,
	__global	t_obj		*objs,
				float3		O,
				float3		D);

#endif
