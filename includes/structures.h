/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/24 13:21:23 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/13 13:57:46 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# define RANGE(x, l1, l2)(x < l1 ? l1 : x > l2 ? l2 : x)
# define TORGB(coef)((uint)(RANGE(coef, 0.0F, 1.0F) * 255.0F + 0.5F))
# define TOHEX(r, g, b)((uint)r * 0x10000 + (uint)g * 0x100 + (uint)b)

typedef enum	e_type {
	SPHERE = 0,
	CYLINDER,
	CONE,
	PLANE,
	ELLIPSOID,
	PARABOLID,
	HYPERBOLOID,
	DISC,
	CUBE,
	TORUS,
	MEBIUS,
	JULIA,
	PYRAMID,
	TRIANGLE,
	MANDELBULB,
	TETRAHEDRON,
	SKYBOX
}				t_type;

typedef enum	e_effect {
	NO_EFFECT = 0,
	NEGATIVE,
	SEPIA,
	GRAYSCALE,
	COMIC,
	BLACK_N_WHITE,
	CASTING,
	OIL,
	ANTIALIASING
}				t_effect;

typedef enum	e_material
{
	DIFFUSE = 0,
	EMISSIVE,
	REFLECT,
	TRANSP,
	GLASS,
	NEGATIVE_FIG
}				t_material;

typedef struct	s_obj
{
	t_material	material;
	short int	type;
	short int	id;
	short int	id_tex;
	short int	id_vt;
	float		rad;
	float		rad2;
	float		spec;
	float		scale;
	float		emission;
	cl_float3	color;
	cl_float3	pos;
	cl_float3	dir;
	cl_float3	dir2;
}				t_obj;

typedef struct	s_vt
{
	cl_float3	vt1;
	cl_float3	vt2;
	cl_float3	vt3;
}				t_vt;

typedef struct	s_viewport
{
	short int	wd_width;
	short int	wd_height;
	float		vw_width;
	float		vw_height;
	float		dist;
}				t_viewport;

#endif
