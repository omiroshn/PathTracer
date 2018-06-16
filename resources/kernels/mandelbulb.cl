/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    mandelbulb.cl                                      :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/05/24 16:18:51 by omiroshn          #+#    #+#              */
/*    Updated: 2018/05/24 16:18:52 by omiroshn         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

float			IterateIntersect(float3 z0)
{
	float3 z = z0;
	float dr = 1.0f;
	float r = 0.0f;
	float degree = 8.0f;

	for (int i = 0; i < 20 ; i++)
	{
		r = fast_length(z);
		if (r > 2.0f) break;

		// convert to polar coordinates
		// float theta = asin(z.z/r);
		float theta = acos(z.z/r);
		float phi = atan2(z.y,z.x);
		// dr =  pow( r, degree - 1.0f) * degree * dr + 1.0f;
		dr = r * r * r * r * r * r * r * degree * dr + 1.0f;

		// scale and rotate the point
		float zr = r * r * r * r * r * r * r * r;
		theta = theta * degree;
		phi = phi * degree;

		// convert back to cartesian coordinates
		// z = zr * (float3){cos(theta) * cos(phi), cos(phi) * sin(theta), sin(theta)};
		z = zr * (float3){sin(theta) * cos(phi), sin(phi) * sin(theta), cos(theta)};
		z += z0;
	}
	return (0.5f * log(r) * r / dr);
}

float2			intersect_ray_mandelbulb(float3 O, float3 D, t_obj *obj)
{
	t_obj intersect_sphere = *obj;
	intersect_sphere.rad = 1.5f;
	float2 sphere = intersect_ray_sphere(O, D, intersect_sphere);
	if (sphere.x == INFINITY && sphere.y == INFINITY)
		return (sphere);

	float totalDistance = 0.0f;
	float steps;
	for (steps = 0.0F; steps < 100.0F; steps++)
	{
		float3 p = O + totalDistance * D;
		float distance = IterateIntersect(p);
		totalDistance += distance;
		if (distance < 0.0005f)
			break;
	}
	obj->spec = 1.0F - steps / 100.0F;
	return ((float2){totalDistance, INFINITY});
}
