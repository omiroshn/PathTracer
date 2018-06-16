/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/12 11:52:31 by pgritsen          #+#    #+#             */
/*   Updated: 2018/06/04 16:26:36 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	move(t_env *env, char state, t_point dir)
{
	float		speed;
	cl_float3	d;

	speed = env->move_speed * (env->flags.sprint + 1) * env->time.delta;
	d = dir_vector(dir, env);
	env->cam->pos = state > 0 ? vec_add(env->cam->pos, vec_mult_num(d, speed))
							: vec_sub(env->cam->pos, vec_mult_num(d, speed));
	init_scene(env);
}

void	movement_keys(SDL_Scancode key, t_env *env, char state)
{
	key == SDL_SCANCODE_W ? env->flags.move_f = state : 0;
	key == SDL_SCANCODE_S ? env->flags.move_b = state : 0;
	key == SDL_SCANCODE_A ? env->flags.sidle_l = state : 0;
	key == SDL_SCANCODE_D ? env->flags.sidle_r = state : 0;
	key == SDL_SCANCODE_SPACE ? env->flags.move_u = state : 0;
	key == SDL_SCANCODE_LCTRL ? env->flags.move_d = state : 0;
	key == SDL_SCANCODE_LSHIFT ? env->flags.sprint = state : 0;
	key == SDL_SCANCODE_KP_PLUS ? env->move_speed *= 1.1 : 0;
	key == SDL_SCANCODE_KP_MINUS ? env->move_speed /= 1.1 : 0;
	key == SDL_SCANCODE_LSHIFT ? env->flags.sprint = state : 0;
}

void	handle_movement(t_env *env)
{
	env->flags.move_f ? move(env, 1, (t_point){0, 0, 1}) : 0;
	env->flags.move_b ? move(env, -1, (t_point){0, 0, 1}) : 0;
	env->flags.sidle_l ? move(env, -1, (t_point){1, 0, 0}) : 0;
	env->flags.sidle_r ? move(env, 1, (t_point){1, 0, 0}) : 0;
	env->flags.move_u ? move(env, 1, (t_point){0, 1, 0}) : 0;
	env->flags.move_d ? move(env, -1, (t_point){0, 1, 0}) : 0;
}

void	view_mousemove(t_env *env)
{
	int		x;
	int		y;

	SDL_GetRelativeMouseState(&x, &y);
	x > 60 ? x = 60 : 0;
	x < -60 ? x = -60 : 0;
	y > 60 ? y = 60 : 0;
	y < -60 ? y = -60 : 0;
	env->cam->rot.x -= (float)y * 0.3F;
	env->cam->rot.y -= (float)x * 0.3F;
	init_scene(env);
}
