/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grevenko <grevenko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 14:32:50 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/12 20:06:19 by grevenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h.cl"
#include "resources/kernels/julia.cl"
#include "resources/kernels/mandelbulb.cl"
#include "resources/kernels/mebius.cl"
#include "resources/kernels/complex.cl"
#include "resources/kernels/solveP4.cl"

/*---------------------------------UTILITIES---------------------------------*/

float	lerp(float v0, float v1, float t)
{
	return (1.0F - t) * v0 + t * v1;
}

float3	lerp3(float3 v0, float3 v1, float t)
{
	return (1.0F - t) * v0 + t * v1;
}

inline static float rand(uint *seed0, uint *seed1)
{
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007FFFFF) | 0x40000000;
	return ((res.f - 2.0F) / 2.0F);
}

inline float3	reflect_ray(float3 R, float3 N)
{
	return (2.0F * N * dot(N, R) - R);
}

float4	qMult(const float4 Q1, const float4 Q2)
{
	float4	R;

	R.x = Q1.x * Q2.x - dot(Q1.yzw, Q2.yzw);
	R.yzw = Q1.x * Q2.yzw + Q2.x * Q1.yzw + cross(Q1.yzw, Q2.yzw);
	return (R);
}

float4 qsqr(const float4 Q)
{
	float4 R;

	R.x = Q.x * Q.x - dot(Q.yzw, Q.yzw);
	R.yzw = 2.0F * Q.x * Q.yzw;
	return (R);
}

inline float	deg_to_rad(float deg)
{
	return (deg * M_PI / 180.0F);
}

float			rgb2luma(float3 rgb)
{
	return rgb.y * (0.587/0.299) + rgb.x;
}

float3			hex_to_rgb(uint hex)
{
	float3	rgb;

	rgb.x = hex >> 16 & 0xFF;
	rgb.y = hex >> 8 & 0xFF;
	rgb.z = hex & 0xFF;
	return (rgb);
}

float3			avg_color(float3 arr[], uint num)
{
	uint	it = 0;
	float3	result = 0.0F;

	while(it < num)
		result += arr[it++];
	return (result / num);
}

float3			get_obj_color(float3 NL, float3 P, t_obj obj,
							__global int2 *textures_info, __global uint *textures,
							__global t_vt *all_vt)
{
	if (obj.id_tex == 0)
		return (obj.color);
	else
	{
		float2			UV;
		int2			tex_pos;
		uint			offset = 0;
		uint			i = -1;
		__global uint	*tex;

		UV = calc_uv(NL, P, obj, all_vt);
		while (++i != (uint)(obj.id_tex - 1))
			offset += textures_info[i].x * textures_info[i].y;
		tex = textures + offset;

		if (obj.scale <= EPSILON)
			obj.scale = 1.0F;

		tex_pos.x = (int)(UV.x * obj.scale * (float)textures_info[i].x) % textures_info[i].x;
		if (tex_pos.x < 0)
			tex_pos.x = textures_info[i].x + tex_pos.x;
		tex_pos.y = (int)(UV.y * obj.scale * (float)textures_info[i].y) % textures_info[i].y;
		if (tex_pos.y < 0)
			tex_pos.y = textures_info[i].y + tex_pos.y;
		tex_pos.y = textures_info[i].y - tex_pos.y - 1;
		return (hex_to_rgb(tex[tex_pos.y * textures_info[i].x + tex_pos.x]) / 256.0F);
	}
}

float3			canvas_to_viewport(float x, float y, t_viewport vwp)
{
	return ((float3){x * vwp.vw_width / vwp.wd_width, y * vwp.vw_height / vwp.wd_height, vwp.dist});
}

float3			rotate_point(float3 rot, float3 D)
{
	float3	sin_c;
	float3	cos_c;
	float3	RX;
	float3	RY;
	float3	RZ;

	sin_c.x = sin(rot.x * M_PI / 180.0F);
	cos_c.x = cos(rot.x * M_PI / 180.0F);
	sin_c.y = sin(rot.y * M_PI / 180.0F);
	cos_c.y = cos(rot.y * M_PI / 180.0F);
	sin_c.z = sin(rot.z * M_PI / 180.0F);
	cos_c.z = cos(rot.z * M_PI / 180.0F);

	RX.x = D.x;
	RX.y = D.y * cos_c.x + D.z * sin_c.x;
	RX.z = D.z * cos_c.x - D.y * sin_c.x;

	RY.x = RX.x * cos_c.y - RX.z * sin_c.y;
	RY.y = RX.y;
	RY.z = RX.z * cos_c.y + RX.x * sin_c.y;

	RZ.x = RY.x * cos_c.z + RY.y * sin_c.z;
	RZ.y = RY.y * cos_c.z - RY.x * sin_c.z;
	RZ.z = RY.z;
	return (RZ);
}

float3			calc_normal(float3 P, float3 D, t_obj obj)
{
	float3		N;
	float3		T;

	N = P - obj.pos;
	if (obj.type == PLANE || obj.type == DISC)
		return (fast_normalize(obj.dir));
	else if (obj.type == CYLINDER || obj.type == CONE)
	{
		if (obj.type == CONE)
			T = fast_normalize(obj.dir - P);
		else if (obj.type == CYLINDER)
			T = fast_normalize(obj.dir - obj.pos);
		N -= T * dot(N, T);
	}
	else if (obj.type == TRIANGLE)
	{
		N = cross(obj.dir2 - obj.pos, obj.dir - obj.pos);
	}
	else if (obj.type == CUBE)
	{
		float3 N_[6];
		float NP[6];
		//front side
		float3	P1 = {obj.pos.x, obj.pos.y, obj.pos.z};
		float3	P2 = {obj.pos.x, obj.pos.y + obj.rad, obj.pos.z};
		float3	P3 = {obj.pos.x + obj.rad2, obj.pos.y + obj.rad, obj.pos.z};
		N_[0] = cross(P3 - P1, P2 - P1);
		NP[0] = dot(N_[0], P - P1);
		//back side
		N_[1] = cross(P2 - P1, P3 - P1);
		P1 = (float3){obj.dir.x, obj.dir.y, obj.dir.z};
		NP[1] = dot(N_[1], P - P1);
		//left side
		P1 = (float3){obj.dir.x, obj.dir.y, obj.dir.z};
		P2 = (float3){obj.dir.x, obj.dir.y + obj.rad, obj.dir.z};
		P3 = (float3){obj.pos.x, obj.pos.y, obj.pos.z};
		N_[2] = cross(P3 - P1, P2 - P1);
		NP[2] = dot(N_[2], P - P1);
		//right side
		N_[3] = cross(P2 - P1, P3 - P1);
		P1 = (float3){obj.dir.x + obj.rad2, obj.dir.y, obj.dir.z};
		NP[3] = dot(N_[3], P - P1);
		//down side
		P1 = (float3){obj.dir.x, obj.dir.y, obj.dir.z};
		P2 = (float3){obj.dir.x + obj.rad2, obj.dir.y, obj.dir.z};
		P3 = (float3){obj.pos.x, obj.pos.y, obj.pos.z};
		N_[4] = cross(P3 - P1, P2 - P1);
		NP[4] = dot(N_[4], P - P1);
		//up side
		N_[5] = cross(P2 - P1, P3 - P1);
		P1 = (float3){obj.dir.x, obj.dir.y + obj.rad, obj.dir.z};
		NP[5] = dot(N_[5], P - P1);

		int i  = -1;
		while (++i < 6)
			if (NP[i] > -EPSILON && NP[i] <= EPSILON)
				break;
		N = N_[i];
	}
	else if (obj.type == PYRAMID)
	{
		float3 N_[5];
		float NP[5];

		float3	A = obj.dir;
		float3	B = {obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
		float3	C = (A + B) / 2.0F;
		C.y += obj.rad2;

		//front side
		float3	P1 = obj.pos;
		float3	P3 = {obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
		N_[0] = cross(P3 - P1, C - P1);
		NP[0] = dot(N_[0], P - P1);
		//back side
		P1 = obj.dir;
		P3 = (float3){obj.dir.x + obj.rad, obj.dir.y, obj.dir.z};
		N_[1] = cross(P3 - P1, C - P1);
		NP[1] = dot(N_[1], P - P1);
		//left side
		P1 = obj.pos;
		P3 = obj.dir;
		N_[2] = cross(P3 - P1, C - P1);
		NP[2] = dot(N_[2], P - P1);
		//right side
		P1 = (float3){obj.dir.x + obj.rad, obj.dir.y, obj.dir.z};
		P3 = (float3){obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
		N_[3] = cross(P3 - P1, C - P1);
		NP[3] = dot(N_[3], P - P1);
		//down side
		P1 = obj.dir;
		float3	P2 = (float3){obj.dir.x + obj.rad, obj.dir.y, obj.dir.z};
		P3 = obj.pos;
		N_[4] = cross(P3 - P1, P2 - P1);
		NP[4] = dot(N_[4], P - P1);

		int i  = -1;
		while (++i < 5)
			if (NP[i] > -EPSILON && NP[i] <= EPSILON)
				break;
		N = N_[i];
	}
	else if (obj.type == TETRAHEDRON)
	{
		float3 N_[4];
		float NP[4];

		float3	A = obj.dir;
		float3	B = obj.pos;
		float3	C = {obj.pos.x + ((obj.dir.x - obj.pos.x) * 2.0f), obj.pos.y, obj.pos.z};
		float3	T = {(A.x + B.x + C.x) / 3.0f, (A.y + B.y + C.y) / 3.0f + obj.rad, (A.z + B.z + C.z) / 3.0f};
		//front side
		float3	P1 = obj.pos;
		float3	P3 = C;
		N_[0] = cross(P3 - P1, T - P1);
		NP[0] = dot(N_[0], P - P1);
		//left side
		P1 = obj.dir;
		P3 = obj.pos;
		N_[1] = cross(P3 - P1, T - P1);
		NP[1] = dot(N_[1], P - P1);
		//right side
		P1 = obj.dir;
		P3 = C;
		N_[2] = cross(P3 - P1, T - P1);
		NP[2] = dot(N_[2], P - P1);
		//down side
		float3	P2 = C;
		P1 = obj.pos;
		P3 = obj.dir;
		N_[3] = cross(P3 - P1, P2 - P1);
		NP[3] = dot(N_[3], P - P1);

		int i  = -1;
		while (++i < 4)
			if (NP[i] > -EPSILON && NP[i] < EPSILON)
				break;
		N = N_[i];
	}
	else if (obj.type == PARABOLID)
	{
		float3 coeff = {3.0F, 1.5F, 5.0F};
		N.x = 2.0F * N.x / coeff.x;
		N.y = -2.0f;
		N.z = 2.0F * N.z / coeff.z;
	}
	else if (obj.type == HYPERBOLOID)
	{
		float3 coeff = {3.0F, 1.5F, 5.0F};
		N.x = 2.0F * N.x / coeff.x;
		N.y = -2.0f * N.y / coeff.y;
		N.z = 2.0F * N.z / coeff.z;
	}
	else if (obj.type == ELLIPSOID)
	{
		float3 coeff = {3.0F, 1.5F, 5.0F};
		N.x = 2.0F * N.x / coeff.x;
		N.y = 2.0F * N.y / coeff.y;
		N.z = 2.0F * N.z / coeff.z;
	}
	else if (obj.type == TORUS)
	{
		float	k = dot(P - obj.pos, fast_normalize(obj.dir));
		float3	A = P - fast_normalize(obj.dir) * k;
		float	m = sqrt(obj.rad * obj.rad - k * k);

		N = P - A - (obj.pos - A) * m / (obj.rad2 + m);
	}
	else if (obj.type == MEBIUS)
	{
		N =  (float3){2.0f * P.x * P.y - 2.0f * obj.rad * P.z - 4.0f * P.x * P.z,
			-obj.rad * obj.rad + P.x * P.x + 3.0f * P.y * P.y - 4.0f * P.y * P.z + P.z * P.z,
			-2.0f * obj.rad * P.x - 2.0f * P.x * P.x - 2.0f * P.y * P.y + 2.0f * P.y * P.z};
	}
	else if (obj.type == MANDELBULB)
	{
		N = (float3)(IterateIntersect(P + D.x) - IterateIntersect(P - D.x),
						IterateIntersect(P + D.y) - IterateIntersect(P - D.y),
						IterateIntersect(P + D.z) - IterateIntersect(P - D.z));
	}
	else if (obj.type == JULIA)
	{
		float4    Z = {P, 0.0F};

		float4    J[4] = {{1.0F, 0.0F, 0.0F, 0.0F},
						{0.0F, 1.0F, 0.0F, 0.0F},
						{0.0F, 0.0F, 1.0F, 0.0F},
						{0.0F, 0.0F, 0.0F, 1.0F}};

		for(int i = 0; i < JULIA_MAX_IT; i++)
		{
			float4    mult[4] = { {Z.x, Z.y, Z.z, Z.w},
								{-Z.y, Z.x, 0, 0},
								{-Z.z, 0, Z.x, 0},
								{-Z.w, 0, 0, Z.x}};

			J[0] = (float4){dot(J[0], mult[0]), dot(J[0], mult[1]), dot(J[0], mult[2]), dot(J[0], mult[3])};
			J[1] = (float4){dot(J[1], mult[0]), dot(J[1], mult[1]), dot(J[1], mult[2]), dot(J[1], mult[3])};
			J[2] = (float4){dot(J[2], mult[0]), dot(J[2], mult[1]), dot(J[2], mult[2]), dot(J[2], mult[3])};
			J[3] = (float4){dot(J[3], mult[0]), dot(J[3], mult[1]), dot(J[3], mult[2]), dot(J[3], mult[3])};

			Z = qsqr(Z) + (float4){obj.pos, -0.046F};

			if (dot(Z, Z) > 4.0F)
				break;
		}

		float4    ret;

		ret = (float4){dot(J[0], Z), dot(J[1], Z), dot(J[2], Z), dot(J[3], Z)};

		N = ret.xyz;
	}
	return (fast_normalize(N));
}

float2			calc_uv(float3 N, float3 P, t_obj obj, __global t_vt *all_vt)
{
	float3	U;
	float3	V;
	float2	ret = 0.0F;

	if (obj.type == SPHERE || obj.type == CYLINDER  || obj.type == CONE || obj.type == TORUS || obj.type == SKYBOX)
	{
		N = -N;
		ret.x = 0.5F + atan2pi(N.z, N.x) / 2.0f;
		if (obj.type == SPHERE || obj.type == SKYBOX)
		{
			ret.y = 0.5F - asin(N.y) / M_PI;
			if (obj.type == SKYBOX)
            	ret.y = 1.0F - ret.y;
		}
		else if (obj.type == CYLINDER)
		{
			float H = fast_length(obj.dir - obj.pos);
			float h = fast_length(P - obj.pos);
			ret.y = sqrt(h * h - obj.rad * obj.rad) / H / 2.0f * obj.rad;
		}
		else if (obj.type == CONE)
		{
			float H = fast_length(obj.dir - obj.pos);
			float h = fast_length(P - obj.dir);
			ret.y = -h / H;
		}
		else if (obj.type == TORUS)
			ret.y = 0.5F + atan2pi(N.y, sqrt(N.x * N.x + N.z * N.z) - obj.rad) / 2.0f;
	}
	else if (obj.type == PLANE || obj.type == DISC || obj.type == CUBE)
	{
		if (N.y >= 0 && N.y <= EPSILON)
			N.y = N.z;
		else if (N.x >= 0 && N.x <= EPSILON)
			N.x = N.z;

		U = fast_normalize((float3){N.y, N.x, 0.0F});
		V = cross(N, U);

		ret.x = 1.0F - dot(U, P);
		ret.y = dot(V, P);
	}
	else if (obj.type == TRIANGLE)
	{
		float3	a = obj.dir - obj.dir2;
		float3	b = obj.pos - obj.dir2;
		float3	c = P - obj.dir2;
		float	aLen = a.x * a.x + a.y * a.y + a.z * a.z;
		float	bLen = b.x * b.x + b.y * b.y + b.z * b.z;
		float	ab = a.x * b.x + a.y * b.y + a.z * b.z;
		float	ac = a.x * c.x + a.y * c.y + a.z * c.z;
		float	bc = b.x * c.x + b.y * c.y + b.z * c.z;
		float	d = aLen * bLen - ab * ab;
		float	u = (aLen * bc - ab * ac) / d;
		float	v = (bLen * ac - ab * bc) / d;
		float	w = 1.0F - u - v;

		float2	v1 = all_vt[obj.id_vt].vt1.xy;
		float2	v2 = all_vt[obj.id_vt].vt2.xy;
		float2	v3 = all_vt[obj.id_vt].vt3.xy;

		ret = v1 * u + v2 * v + v3 * w;
		ret.x = 1.0F - ret.x;
	}
	return (ret);
}

float			fix_limits(float3 O, float3 D, float3 Va, t_obj obj, float ints)
{
	float3	Q;

	Q = O + D * ints;
	if (dot(Va, Q - obj.dir) < 0 && obj.type == PARABOLID)
		return (ints);
	else if (obj.type == HYPERBOLOID)
	{
		float3 P = (obj.pos - obj.dir) / fast_length(obj.pos - obj.dir) * fast_length(obj.dir - obj.pos) + obj.pos;
		if (dot((P - obj.pos) / fast_length(P - obj.pos), Q - P) < 0 && dot(Va, Q - obj.dir) < 0)
			return (ints);
	}
	else if (dot(Va, Q - obj.pos) > 0 && dot(Va, Q - obj.dir) < 0)
		return (ints);
	return (INFINITY);
}

/*-------------------------------INTERSECTIONS-------------------------------*/

float2			intersect_ray_plane(float3 O, float3 D, t_obj obj)
{
	float2	T;
	float	k1;
	float	k2;

	obj.dir /= fast_length(obj.dir);
	k1 = dot(D, obj.dir);
	k2 = dot(O - obj.pos, obj.dir);
	if (k1 != 0.0F)
	{
		T.x = -k2 / k1;
		T.y = INFINITY;
		return (T);
	}
	return ((float2){INFINITY, INFINITY});
}

float2			intersect_ray_cylinder(float3 O, float3 D, t_obj *obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float2	T;
	t_obj	u_disc;
	t_obj	d_disc;
	float2	UC;
	float2	DC;
	float3	D_Va;
	float3	OC_Va;
	float3	Va = (obj->dir - obj->pos) / fast_length(obj->dir - obj->pos);

	D_Va = D - dot(D, Va) * Va;
	OC_Va = (O - obj->dir) - dot((O - obj->dir), Va) * Va;
	k1 = dot(D_Va, D_Va);
	k2 = 2.0F * dot(D_Va, OC_Va);
	k3 = dot(OC_Va, OC_Va) - obj->rad * obj->rad;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	T = (float2){
		(-k2 - sqrt(descr)) / (2.0F * k1),
		(-k2 + sqrt(descr)) / (2.0F * k1)};

	Va = fast_normalize(obj->dir - obj->pos);

	u_disc = (t_obj){.pos = obj->dir, .dir = Va, .rad = obj->rad};
	d_disc = (t_obj){.pos = obj->pos, .dir = Va, .rad = obj->rad};

	UC = intersect_ray_disc(O, D, u_disc);
	DC = intersect_ray_disc(O, D, d_disc);

	T.x = fix_limits(O, D, Va, *obj, T.x);
	T.y = fix_limits(O, D, Va, *obj, T.y);

	if (UC.x < T.x || DC.x < T.x)
		T.x = fmin(UC.x, DC.x);
	if (UC.y < T.y || DC.y < T.y)
		T.y = fmin(UC.y, DC.y);

	k1 = fmin(T.x, T.y);
	if (k1 == UC.x || k1 == UC.y || k1 == DC.x || k1 == DC.y)
	{
		obj->dir = obj->pos - obj->dir;
		obj->type = DISC;
	}

	return (T);
}

float2			intersect_ray_cone(float3 O, float3 D, t_obj *obj)
{
	float	descr;
	float	alpha = deg_to_rad(obj->rad);
	float	k1;
	float	k2;
	float	k3;
	float	dva;
	float	ocva;
	t_obj	cap;
	float2	C;
	float2	t_alpha = {sin(alpha), cos(alpha)};
	float2	T;
	float3	D_Va;
	float3	OC_Va;
	float3	Va = fast_normalize(obj->dir - obj->pos);

	dva = dot(D, Va);
	ocva = dot((O - obj->dir), Va);
	D_Va = D - dva * Va;
	OC_Va = (O - obj->dir) - ocva * Va;

	k1 = t_alpha.y * t_alpha.y * dot(D_Va, D_Va) - t_alpha.x * t_alpha.x * dva * dva;
	k2 = 2.0F * t_alpha.y * t_alpha.y * dot(D_Va, OC_Va) - 2.0F * t_alpha.x * t_alpha.x * dva * ocva;
	k3 = t_alpha.y * t_alpha.y * dot(OC_Va, OC_Va) - t_alpha.x * t_alpha.x * ocva * ocva;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	T = (float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)};
	T.x = fix_limits(O, D, Va, *obj, T.x);
	T.y = fix_limits(O, D, Va, *obj, T.y);

	cap = (t_obj){.pos = obj->pos, .dir = fast_normalize(obj->pos - obj->dir), .rad = tan(alpha) * fast_length(obj->dir - obj->pos)};
	C = intersect_ray_disc(O, D, cap);

	if (T.x != INFINITY)
		T.x = fmin(C.x, T.x);
	if (T.y != INFINITY)
		T.y = fmin(C.y, T.y);
	k1 = fmin(T.x, T.y);
	if ((k1 == C.x || k1 == C.y) && k1 != INFINITY)
	{
		obj->dir = obj->dir - obj->pos;
		obj->type = DISC;
	}

	return (T);
}

float2			intersect_ray_sphere(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float3	OC;

	OC = O - obj.pos;

	k1 = dot(D, D);
	k2 = 2.0F * dot(OC, D);
	k3 = dot(OC, OC) - obj.rad * obj.rad;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0.0F)
		return ((float2){INFINITY, INFINITY});
	return ((float2){
		(-k2 - sqrt(descr)) / (2.0F * k1),
		(-k2 + sqrt(descr)) / (2.0F * k1)});
}

float2			intersect_ray_ellipsoid(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float3	OC;

	OC = O - obj.pos;
	float3 coeff = {3.0F, 1.5F, 5.0F};
	k1 = (D.x * D.x / coeff.x) + (D.y * D.y / coeff.y) + (D.z * D.z / coeff.z);
	k2 = (2.0F * OC.x * D.x / coeff.x) + (2.0F * OC.y * D.y / coeff.y) + (2.0F * OC.z * D.z / coeff.z);
	k3 =  (OC.x * OC.x / coeff.x) + (OC.y * OC.y / coeff.y) + (OC.z * OC.z / coeff.z) - obj.rad * obj.rad;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	return ((float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)});
}

float2			intersect_ray_parabolid(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float2	T;
	float3	OC;
	float3	Va = (obj.dir - obj.pos) / fast_length(obj.dir - obj.pos);

	OC = O - obj.pos;
	float3 coeff = {3.0F, 1.5F, 5.0F};
	k1 = (D.x * D.x / coeff.x) + (D.z * D.z / coeff.z);
	k2 = (2.0F * OC.x * D.x / coeff.x) + (2.0F * OC.z * D.z / coeff.z) - D.y;
	k3 =  (OC.x * OC.x / coeff.x) + (OC.z * OC.z / coeff.z) - OC.y;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	T = (float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)};
	T.x = fix_limits(O, D, Va, obj, T.x);
	T.y = fix_limits(O, D, Va, obj, T.y);
	return (T);
}

float2			intersect_ray_hyperboloid(float3 O, float3 D, t_obj obj)
{
	float	descr;
	float	k1;
	float	k2;
	float	k3;
	float2	T;
	float3	OC;
	float3	Va = (obj.dir - obj.pos) / fast_length(obj.dir - obj.pos);

	OC = O - obj.pos;
	float3 coeff = {3.0F, 1.5F, 5.0F};
	k1 = (D.x * D.x / coeff.x) - (D.y * D.y / coeff.y) + (D.z * D.z / coeff.z);
	k2 = (2.0F * OC.x * D.x / coeff.x) - (2.0F * OC.y * D.y / coeff.y) + (2.0F * OC.z * D.z / coeff.z);
	k3 =  (OC.x * OC.x / coeff.x) - (OC.y * OC.y / coeff.y) + (OC.z * OC.z / coeff.z) + obj.rad;

	descr = k2 * k2 - 4.0F * k1 * k3;
	if (descr < 0)
		return ((float2){INFINITY, INFINITY});
	T = (float2){
		(-k2 + sqrt(descr)) / (2.0F * k1),
		(-k2 - sqrt(descr)) / (2.0F * k1)};
	T.x = fix_limits(O, D, Va, obj, T.x);
	T.y = fix_limits(O, D, Va, obj, T.y);
	return (T);
}

float2			intersect_ray_disc(float3 O, float3 D, t_obj obj)
{
	float2	T = intersect_ray_plane(O, D, obj);

	if (T.x != INFINITY)
	{
		float3	P = O + D * T.x;
		float3	V = P - obj.pos;
		float	d2 = sqrt(dot(V, V));

		if (d2 <= obj.rad)
			return ((float2){T.x, INFINITY});
	}
	return ((float2){INFINITY, INFINITY});
}

inline static float	intersect_ray_triangle(float3 P1, float3 P2, float3 P3, float3 O, float3 D)
{
	float3 e1 = P2 - P1;
	float3 e2 = P3 - P1;
	float3 pvec = cross(D, e2);
	float det = dot(e1, pvec);

	if (det < 1e-8f && det > -1e-8f) {
		return INFINITY;
	}

	float inv_det = 1.0f / det;
	float3 tvec = O - P1;
	float u = dot(tvec, pvec) * inv_det;
	if (u < 0 || u > 1) {
		return INFINITY;
	}

	float3 qvec = cross(tvec, e1);
	float v = dot(D, qvec) * inv_det;
	if (v < 0 || u + v > 1) {
		return INFINITY;
	}
	return dot(e2, qvec) * inv_det;
}

float2			intersect_ray_cube(float3 O, float3 D, t_obj obj)
{
	//front
	float3	P1 = {obj.pos.x, obj.pos.y, obj.pos.z};
	float3	P2 = {obj.pos.x, obj.pos.y + obj.rad, obj.pos.z};
	float3	P3 = {obj.pos.x + obj.rad2, obj.pos.y + obj.rad, obj.pos.z};
	float3	P4 = {obj.pos.x + obj.rad2, obj.pos.y, obj.pos.z};
	float T = intersect_ray_triangle(P1, P2, P4, O, D);
	T == INFINITY ? T = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	//back
	P1 = (float3){obj.dir.x, obj.dir.y, obj.dir.z};
	P2 = (float3){obj.dir.x, obj.dir.y + obj.rad, obj.dir.z};
	P3 = (float3){obj.dir.x + obj.rad2, obj.dir.y + obj.rad, obj.dir.z};
	P4 = (float3){obj.dir.x + obj.rad2, obj.dir.y, obj.dir.z};
	float T1 = intersect_ray_triangle(P1, P2, P4, O, D);
	T1 == INFINITY ? T1 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	T1 < T ? T = T1 : 0;
	// //left
	P1 = (float3){obj.dir.x, obj.dir.y, obj.dir.z};
	P2 = (float3){obj.dir.x, obj.dir.y + obj.rad, obj.dir.z};
	P3 = (float3){obj.pos.x, obj.pos.y + obj.rad, obj.pos.z};
	P4 = (float3){obj.pos.x, obj.pos.y, obj.pos.z};
	float T2 = intersect_ray_triangle(P1, P2, P4, O, D);
	T2 == INFINITY ? T2 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	// //right
	P1 = (float3){obj.dir.x + obj.rad2, obj.dir.y, obj.dir.z};
	P2 = (float3){obj.dir.x + obj.rad2, obj.dir.y + obj.rad, obj.dir.z};
	P3 = (float3){obj.pos.x + obj.rad2, obj.pos.y + obj.rad, obj.pos.z};
	P4 = (float3){obj.pos.x + obj.rad2, obj.pos.y, obj.pos.z};
	float T3 = intersect_ray_triangle(P1, P2, P4, O, D);
	T3 == INFINITY ? T3 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	T3 < T2 ? T2 = T3 : 0;
	// //down
	P1 = (float3){obj.dir.x, obj.dir.y, obj.dir.z};
	P2 = (float3){obj.dir.x + obj.rad2, obj.dir.y, obj.dir.z};
	P3 = (float3){obj.pos.x + obj.rad2, obj.pos.y, obj.pos.z};
	P4 = (float3){obj.pos.x, obj.pos.y, obj.pos.z};
	float T4 = intersect_ray_triangle(P1, P2, P4, O, D);
	T4 == INFINITY ? T4 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	// //up
	P1 = (float3){obj.dir.x, obj.dir.y + obj.rad, obj.dir.z};
	P2 = (float3){obj.dir.x + obj.rad2, obj.dir.y + obj.rad, obj.dir.z};
	P3 = (float3){obj.pos.x + obj.rad2, obj.pos.y + obj.rad, obj.pos.z};
	P4 = (float3){obj.pos.x, obj.pos.y + obj.rad, obj.pos.z};
	float T5 = intersect_ray_triangle(P1, P2, P4, O, D);
	T5 == INFINITY ? T5 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;
	T5 < T4 ? T4 = T5 : 0;

	T2 < T ? T = T2 : 0;
	T4 < T ? T = T4 : 0;
	return ((float2)(T, INFINITY));
}

float2	intersect_ray_piramid(float3 O, float3 D, t_obj obj)
{
	float3	A = obj.dir;
	float3	B = {obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
	float3	C = (A + B) / 2.0F;
	C.y += obj.rad2;
	//front
	float3	P1 = obj.pos;
	float3	P2 = {obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
	float T = intersect_ray_triangle(P1, P2, C, O, D);
	//back
	P1 = obj.dir;
	P2 = (float3){obj.dir.x + obj.rad, obj.dir.y, obj.dir.z};
	float T1 = intersect_ray_triangle(P1, P2, C, O, D);
	T1 < T ? T = T1 : 0;
	// //left
	P1 = obj.dir;
	P2 = obj.pos;
	float T2 = intersect_ray_triangle(P1, P2, C, O, D);
	// //right
	P1 = (float3){obj.dir.x + obj.rad, obj.dir.y, obj.dir.z};
	P2 = (float3){obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
	float T3 = intersect_ray_triangle(P1, P2, C, O, D);
	T3 < T2 ? T2 = T3 : 0;
	// //down
	P1 = obj.dir;
	P2 = (float3){obj.dir.x + obj.rad, obj.dir.y, obj.dir.z};
	float3	P3 = (float3){obj.pos.x + obj.rad, obj.pos.y, obj.pos.z};
	float3	P4 = obj.pos;
	float T4 = intersect_ray_triangle(P1, P2, P4, O, D);
	T4 == INFINITY ? T4 = intersect_ray_triangle(P3, P2, P4, O, D) : 0;

	T2 < T ? T = T2 : 0;
	T4 < T ? T = T4 : 0;
	return ((float2)(T, INFINITY));
}

float2			intersect_ray_tetrahedron(float3 O, float3 D, t_obj obj)
{
	float3	A = obj.dir;
	float3	B = obj.pos;
	float3	C = {obj.pos.x + ((obj.dir.x - obj.pos.x) * 2.0f), obj.pos.y, obj.pos.z};
	float3	T = { (A.x + B.x + C.x) / 3.0f, (A.y + B.y + C.y) / 3.0f + obj.rad, (A.z + B.z + C.z) / 3.0f };
	//front
	float3	P1 = obj.pos;
	float3	P2 = C;
	float T1 = intersect_ray_triangle(P1, P2, T, O, D);
	// //left
	P1 = obj.dir;
	P2 = obj.pos;
	float T2 = intersect_ray_triangle(P1, P2, T, O, D);
	T2 < T1 ? T1 = T2 : 0;
	// //right
	P2 = C;
	float T3 = intersect_ray_triangle(P1, P2, T, O, D);
	// //down
	P1 = obj.pos;
	P2 = obj.dir;
	float T4 = intersect_ray_triangle(P1, P2, C, O, D);
	T4 < T3 ? T3 = T4 : 0;

	T3 < T1 ? T1 = T3 : 0;
	return ((float2)(T1, INFINITY));
}


static float2	intersect_ray_torus(float3 O, float3 Dir, t_obj obj)
{
	t_obj intersect_sphere = obj;
	intersect_sphere.rad = obj.rad + obj.rad2;
	float2 sphere = intersect_ray_sphere(O, Dir, intersect_sphere);
	if (sphere.x == INFINITY && sphere.y == INFINITY)
		return (sphere);

	float r2 = pow(obj.rad, 2.0F);
	float R2 = pow(obj.rad2, 2.0F);

	float3 OC = O - obj.pos;
	float m = dot(Dir, Dir);
	float n = dot(OC, Dir);
	float o = dot(OC, OC);
	float p = dot(Dir, fast_normalize(obj.dir));
	float q = dot(OC, fast_normalize(obj.dir));
	float a4 = m * m;
	float a3 = 4.0F * m * n;
	float a2 = 4.0F * n * n + 2.0F * m * (o - r2 - R2) + 4.0F * R2 * p * p;
	float a1 = 4.0F * n * (o - r2 - R2) + 8.0F * R2 * p * q;
	float a0 = pow(o - r2 - R2, 2.0F) + 4.0F * R2 * q * q - 4.0F * R2 * r2;

	a3 /= a4; a2 /= a4; a1 /= a4; a0 /= a4;

	float roots[4];
	int n_real_roots;
	n_real_roots = SolveP4(roots, a3, a2, a1, a0);

	if (!n_real_roots)
		return ((float2){INFINITY, INFINITY});

	float root = 0.0f;
	for (int i = 0; i < n_real_roots; i++)
	{
		!i ? root = roots[i] : 0;
		roots[i] < root ? root = roots[i] : 0;
	}
	return ((float2){root + 0.01f, INFINITY});
}

static float2	intersect_ray_skybox(float3 O, float3 D, t_obj *obj)
{
	obj->scale = 1;
	obj->material = EMISSIVE;
	obj->emission = 0.5F;
	obj->rad = SKYBOX_RADIUS;
	obj->pos = 0;

	return (intersect_ray_sphere(O, D, *obj));
}

float2			choose_intersection(float3 O, float3 D, t_obj *obj, int type)
{
	if (type == SPHERE)
		return (intersect_ray_sphere(O, D, *obj));
	else if (type == PLANE)
		return (intersect_ray_plane(O, D, *obj));
	else if (type == CYLINDER)
		return (intersect_ray_cylinder(O, D, obj));
	else if (type == CONE)
		return (intersect_ray_cone(O, D, obj));
	else if (type == ELLIPSOID)
		return (intersect_ray_ellipsoid(O, D, *obj));
	else if (type == PARABOLID)
		return (intersect_ray_parabolid(O, D, *obj));
	else if (type == HYPERBOLOID)
		return (intersect_ray_hyperboloid(O, D, *obj));
	else if (type == DISC)
		return (intersect_ray_disc(O, D, *obj));
	else if (type == CUBE)
		return (intersect_ray_cube(O, D, *obj));
	else if (type == PYRAMID)
		return(intersect_ray_piramid(O, D, *obj));
	else if (type == TETRAHEDRON)
		return(intersect_ray_tetrahedron(O, D, *obj));
	else if (type == JULIA)
		return(intersect_ray_julia(O - obj->dir2, D, obj));
	else if (type == MANDELBULB)
		return(intersect_ray_mandelbulb(O - obj->dir2, D, obj));
	else if (type == TORUS)
		return(intersect_ray_torus(O, D, *obj));
	else if (type == MEBIUS)
		return(intersect_ray_mebius(O - obj->dir2, D, *obj));
	else if (type == TRIANGLE)
		return ((float2){intersect_ray_triangle(obj->pos, obj->dir, obj->dir2, O, D), INFINITY});
	else if (type == SKYBOX)
		return (intersect_ray_skybox(O, D, obj));
	else
		return ((float2){INFINITY, INFINITY});
}

t_obj_data		closest_intersection(float3 O, float3 D, __global t_obj *objs)
{
	t_obj		tmp;
	t_obj_data	obj_data;
	float2		T;
	int			it = -1;

	obj_data.closest_t = INFINITY;
	obj_data.longest_t = 0.0F;
	obj_data.obj.type = -1;
	while (objs[++it].type >= 0)
	{
		tmp = objs[it];
		T = choose_intersection(O, D, &tmp, objs[it].type);
		if (T.x > 0.0F && T.x < obj_data.closest_t)
		{
			obj_data.closest_t = T.x;
			obj_data.longest_t = T.y;
			obj_data.obj = tmp;
		}
		if (T.y > 0.0F && T.y < obj_data.closest_t)
		{
			obj_data.closest_t = T.y;
			obj_data.longest_t = T.x;
			obj_data.obj = tmp;
		}
	}
	return (obj_data);
}

float3			randomHemisphereDirection(float3 NL, uint *seed0, uint *seed1)
{
	float3		U;
	float		r1, r2, r2s;

	r1 = 2.0F * M_PI * rand(seed0, seed1);
	r2 = rand(seed0, seed1);
	r2s = native_sqrt(r2);

	U = fast_normalize(cross(fabs(NL.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f), NL));
	return (fast_normalize(U * native_cos(r1) * r2s + cross(NL, U) * native_sin(r1) * r2s + NL * native_sqrt(1.0f - r2)));
}

float			fresnelReflectAmount(float n1, float n2, float3 NL, float3 D, float spec)
{
	float r0 = (n1 - n2) / (n1 + n2);
	float cosX = -dot(NL, D);

	if (n1 > n2)
	{
		float n = n1 / n2;
		float sinT2 = n * n * (1.0F - cosX * cosX);
		if (sinT2 > 1.0F)
			return (1.0F);
		cosX = sqrt(1.0F - sinT2);
	}

	float x;
	float ret;

	x = 1.0F - cosX;
	ret = r0 * r0 + (1.0F - r0 * r0) * x * x * x * x * x;

	ret = (spec + (1.0F - spec) * ret);
	return (ret);
}

float3			reflectHemisphereDirection(t_obj *obj, bool *phong, float3 NL, float3 D, uint *seed0, uint *seed1)
{
	if (!obj->spec)
		obj->spec = 1.0F;
	else if (obj->spec < 0.0F)
		obj->spec = 0.0F;
	else if (obj->spec > 1.0F)
		obj->spec = 1.0F;

	if (obj->spec && rand(seed0, seed1) <= fresnelReflectAmount(1.0F, 1.5F, NL, D, obj->spec))
	{
		*phong = false;
		return (reflect_ray(-D, NL));
	}
	else
		return (randomHemisphereDirection(NL, seed0, seed1));
}

float3			transparentDirection(t_obj *obj, bool *phong, float3 NL, float3 D, uint *seed0, uint *seed1)
{
	if (obj->spec < 0.0F)
		obj->spec = 0.0F;
	else if (obj->spec > 0.8F)
		obj->spec = 0.8F;

	*phong = false;
	if (obj->spec && rand(seed0, seed1) <= fresnelReflectAmount(1.0F, 1.5F, NL, D, obj->spec))
		return (reflect_ray(-D, NL));
	return (D);
}

float3			glassRefractionDirection(t_obj *obj, float3 NL, float3 N, float3 *O, float3 D, float3 P, float3 *mask, uint *seed0, uint *seed1)
{
	bool	into = dot(N, NL) > 0;
	float	nc = 1.0F;
	float	nt = 1.5F;
	float	nnt = into ? nc / nt : nt / nc;
	float	ddn = dot(D, NL);
	float	cos2t;

	if ((cos2t = 1.0F - nnt * nnt * (1.0F - ddn * ddn)) < 0) {
		*O = P + NL * EPSILON;
		return (reflect_ray(-D, NL));
	} else {
		float3	refr_dir = fast_normalize(D * nnt - N * ((into ? 1.0F : -1.0F) * (ddn * nnt + sqrt(cos2t))));
		float	a = nt - nc;
		float	b = nt + nc;
		float	R0 = a * a / (b * b);
		float	c = 1.0F - (into ? -ddn : dot(refr_dir, N));
		float	Re = R0 + (1.0F - R0) * c * c * c * c * c;
		float	Tr = 1.0F - Re;
		float	Pt = obj->spec + 0.5F * Re;
		float	RP = Re / Pt;
		float	TP = Tr / (1.0F - Pt);

		if (rand(seed0, seed1) < Pt) {
			*mask *= RP;
			*O = P + NL * EPSILON;
			return (reflect_ray(-D, NL));
		} else {
			*mask *= TP;
			*O = P - NL * EPSILON;
			return (refr_dir);
		}
	}
}

/*--------------------------------PATHTRACING--------------------------------*/

float3			trace_ray(float3 O, float3 D, __global t_obj *objs,
							uint *seed0, uint *seed1, float ambient_light,
							__global int2 *textures_info, __global uint *textures,
							__global t_vt *all_vt)
{
	t_obj_data	obj_data;

	float3		P;
	float3		N;
	float3		NL;

	float3		final_color = 0.0F;
	float3		mask = 1.0F;
	float3		emission = 0.0F;

	bool		phong;
	bool		mix_colors;

	int	bounce = -1;
	while (++bounce < BOUNCE_DEPTH)
	{
		mix_colors = true;
		phong = true;
		obj_data = closest_intersection(O, D, objs);
		if (obj_data.obj.type < 0)
			break ;
		P = O + obj_data.closest_t * D;
		if (obj_data.obj.type == MEBIUS || obj_data.obj.type == MANDELBULB || obj_data.obj.type == JULIA)
			N = calc_normal((O - obj_data.obj.dir2) + obj_data.closest_t * D, D, obj_data.obj);
		else
			N = calc_normal(P, D, obj_data.obj);
		NL = dot(N, D) > 0.0F && obj_data.obj.type != TORUS ? N * (-1.0F) : N;

		if (obj_data.obj.type == MANDELBULB || obj_data.obj.type == JULIA)
		{
			final_color = obj_data.obj.spec * N;
			final_color += mask * ambient_light / 10.0F;
			break ;
		}
		obj_data.obj.color = get_obj_color(NL, P, obj_data.obj, textures_info, textures, all_vt);
		emission = (obj_data.obj.material == EMISSIVE ? obj_data.obj.emission : 0.0F) * obj_data.obj.color;
		if (dot(emission, emission) < 0.0F)
			emission = 0.0F;

		final_color += mask * (emission + ambient_light / 10.0F);

		if (obj_data.obj.material == REFLECT)
		{
			O = P + NL * EPSILON;
			D = reflectHemisphereDirection(&obj_data.obj, &phong, NL, D, seed0, seed1);
		}
		else if (obj_data.obj.material == GLASS)
		{
			phong = false;
			D = glassRefractionDirection(&obj_data.obj, NL, N, &O, D, P, &mask, seed0, seed1);
		}
		else if (obj_data.obj.material == TRANSP)
		{
			O = P - NL * EPSILON;
			D = transparentDirection(&obj_data.obj, &phong, NL, D, seed0, seed1);
		}
		else if (obj_data.obj.material == NEGATIVE_FIG)
		{
			if (obj_data.longest_t != INFINITY)
				P = O + obj_data.longest_t * D;
			O = P + D * 0.01F;
			mix_colors = false;
		}
		else
		{
			O = P + NL * EPSILON;
			D = randomHemisphereDirection(NL, seed0, seed1);
		}

		if (mix_colors)
		{
			if (obj_data.obj.type == MANDELBULB)
				mask *= obj_data.obj.spec;
			mask *= obj_data.obj.color;
			if (phong)
				mask *= fabs(dot(D, NL));
			mask *= 2.0F;
		}
	}
	return (final_color);
}


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
				char		smooth)
{
	const int	SMOOTH_LEVEL = smooth;
	short int	screen_x = get_global_id(0);
	short int	screen_y = get_global_id(1);
	short int	x = screen_x - vwp.wd_width / 2;
	short int	y = vwp.wd_height / 2 - screen_y;
	uint		seed0 = random_seed * screen_x;
	uint		seed1 = random_seed * screen_y;
	int			itx = -1;
	int			ity = -1;
	float3		result_color;
	float3		color[9] = {0};
	float3		D;

	while (++itx < SMOOTH_LEVEL && (ity = -1))
		while (++ity < SMOOTH_LEVEL)
		{
			D = rotate_point(rot, canvas_to_viewport(x + (itx + 0.5) / SMOOTH_LEVEL, y + (ity + 0.5) / SMOOTH_LEVEL, vwp));
			color[ity * SMOOTH_LEVEL + itx] = trace_ray(O, D, objs, &seed0, &seed1, ambient_light, textures_info, textures, all_vt);
		}

	result_color = colors[screen_y * vwp.wd_width + screen_x];

	result_color *= total_samples - 1;
	result_color += avg_color(color, SMOOTH_LEVEL * SMOOTH_LEVEL);
	result_color /= total_samples;

	output[screen_y * vwp.wd_width + screen_x] = TOHEX(TORGB(result_color.x),
														TORGB(result_color.y),
														TORGB(result_color.z));
	colors[screen_y * vwp.wd_width + screen_x] = result_color;
}

__kernel void
intersect_figure(
	__global	t_obj		*obj,
	__global	t_obj		*objs,
				float3		O,
				float3		D)
{
	t_obj_data	obj_data;

	obj_data = closest_intersection(O, D, objs);
	if (obj_data.obj.type >= 0)
		*obj = obj_data.obj;
	else
		obj->type = -1;
}

__kernel void
apply_effects(
	__global	uint		*io,
				t_effect	type,
	__global	uint		*out)
{
	float3		color;
	float3		tmp;
	uint		avg;
	short int	x = get_global_id(0);
	short int	y = get_global_id(1);
	short int	w = get_global_size(0);
	short int	h = get_global_size(1);

	color = hex_to_rgb(io[y * w + x]);

	if (type == NEGATIVE)
		color = 256.0F - color;
	else if (type == GRAYSCALE)
		color = (color.x + color.y + color.z) / 3.0F;
	else if (type == SEPIA)
	{
		color.x = 0.299F * color.x + 0.587F * color.y + 0.114F * color.z;
		color.y = 0.299F * color.x + 0.587F * color.y + 0.114F * color.z;
		color.z = 0.299F * color.x + 0.587F * color.y + 0.114F * color.z;
	}
	else if (type == COMIC)
	{
		tmp = color;
		color.x = fabs(tmp.y - tmp.z + tmp.y + tmp.x) * tmp.x / 256.0F;
		color.y = fabs(tmp.z - tmp.y + tmp.z + tmp.x) * tmp.x / 256.0F;
		color.z = fabs(tmp.z - tmp.y + tmp.z + tmp.x) * tmp.y / 256.0F;
	}
	else if (type == BLACK_N_WHITE)
	{
		avg = (color.x + color.y + color.z) / 3.0F;
		if (avg > 100)
			color = 255.0F;
		else
			color = 0.0F;
	}
	else if (type == CASTING)
	{
		color.x = color.x * 128.0F / (color.y + color.z + 1.0F);
		color.y = color.y * 128.0F / (color.x + color.z + 1.0F);
		color.z = color.z * 128.0F / (color.y + color.x + 1.0F);
	}
	else if (type == OIL && (x > OIL_FILTER_OFFSET || x < w - OIL_FILTER_OFFSET
			|| y > OIL_FILTER_OFFSET || y < h - OIL_FILTER_OFFSET))
	{
		float3	tmp = 0;

		int		byteOffset = y * w + x;
		int		calcOffset = 0;
		int		currentIntensity = 0;
		int		maxIntensity = 0;
		int		maxIndex = 0;

		float	intensityBin[OIL_LEVELS + 1] = {0};
		float3	colors[OIL_LEVELS + 1] = {0};

		for (int filterY = -OIL_FILTER_OFFSET; filterY <= OIL_FILTER_OFFSET; filterY++)
		{
			for (int filterX = -OIL_FILTER_OFFSET; filterX <= OIL_FILTER_OFFSET; filterX++)
			{
				calcOffset = byteOffset + filterX + (filterY * w);

				tmp = hex_to_rgb(io[calcOffset]);

				currentIntensity = ((tmp.x + tmp.y + tmp.z) / (3.0F * OIL_LEVELS)) / 255.0F;

				intensityBin[currentIntensity] += 1;
				colors[currentIntensity] += tmp;

				if (intensityBin[currentIntensity] > maxIntensity)
				{
					maxIntensity = intensityBin[currentIntensity];
					maxIndex = currentIntensity;
				}
			}
		}


		color = clamp(colors[maxIndex] / maxIntensity, 0.0F, 255.0F);
	}
	out[y * w + x] = (uint)color.x * 0x10000 + (uint)color.y * 0x100 + (uint)color.z;
}
