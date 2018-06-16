/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    julia.cl                                           :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: omiroshn <marvin@42.fr>                    +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/05/18 21:25:43 by omiroshn          #+#    #+#              */
/*    Updated: 2018/05/18 21:25:44 by omiroshn         ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

float2			intersect_ray_julia(float3 O, float3 D, t_obj *obj)
{
	float	dist = 0.0F;
	float	normZ;
	float	normZP;
	float4	R = {O, 0.0F};
	float	steps = 0;

	do
	{
		steps++;
		float4 Z = R;
		float4 ZP = {1.0F, 0.0F, 0.0F, 0.0F};

		for (int i = 0; i < JULIA_MAX_IT; i++)
		{
			ZP = 2.0F * qMult(Z, ZP);
			Z = qsqr(Z) + (float4){obj->pos, -0.046F};
			if (dot(Z, Z) > ESCAPE_THRESHOLD)
				break;
		}

		normZP = fast_length(ZP);
		if (normZP == 0.0F)
			break;

		normZ = fast_length(Z);
		dist = 0.5F * normZ * log(normZ) / normZP;

		R += (float4)(D, 0.0F) * dist;

		if (dot(R, R) > 4.0F)
			return ((float2){INFINITY, INFINITY});
	}
	while (dist > EPSILON * 50.0F);
	obj->spec = 1.0F - steps / 40.0F;
	return ((float2){fast_distance(O, R.xyz), INFINITY});
}
