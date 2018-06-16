/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 20:05:02 by pgritsen          #+#    #+#             */
/*   Updated: 2018/05/26 19:58:54 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	display_fps(SDL_Renderer *rend, t_env *env)
{
	char		s[512];
	static uint	frame_rate;
	uint		t_c;
	static uint	t_p;
	static uint	c_b;

	t_c = time(NULL);
	env->time.delta = SDL_GetTicks() - c_b;
	if (t_c - t_p && (t_p = t_c))
		frame_rate = 1000.0 / env->time.delta;
	c_b = SDL_GetTicks();
	sprintf(s, "FPS: %u", frame_rate);
	sgl_draw_str(s, &(t_font){"SourceSans", 12, 0xEEEEEE, 0},
							(t_point){5, 5, 0}, rend);
}

void	display_render_time(t_env *env, SDL_Renderer *rend)
{
	static char	s[512] = {0};
	float		sec;
	uint		min;
	uint		hours;
	uint		d;

	if (env->flags.pause)
		env->scene.timestamp += env->time.delta;
	sec = (SDL_GetTicks() - env->scene.timestamp) / 1000.0F;
	min = (uint)sec / 60;
	hours = min / 60;
	d = hours / 24;
	sec = fmod(sec, 60.0F);
	if (d > 0 && !env->flags.pause)
		sprintf(s, "Time: %u d %u h %u m %.2f s", d, hours % 24, min % 60, sec);
	else if (hours > 0 && !env->flags.pause)
		sprintf(s, "Time: %u h %u m %.2f s", hours, min % 60, sec);
	else if (min > 0 && !env->flags.pause)
		sprintf(s, "Time: %u m %.2f s", min, sec);
	else if (!env->flags.pause)
		sprintf(s, "Time: %.2f s", sec);
	sgl_draw_str(s, &(t_font){"SourceSans", 12, 0xEEEEEE, 0},
					(t_point){5, 25, 0}, rend);
}

uint	stats_handler(int x, int y)
{
	uint				ret;

	ret = 0;
	if (x >= 5 && x <= 155 && y >= 5 && y <= 50)
		ret++;
	return (ret);
}

void	display_stats(t_env *env, SDL_Renderer *rend)
{
	char			s[512];
	const SDL_Rect	p = {0, 0, 150, 46};

	SDL_SetRenderDrawColor(rend, 0x22, 0x22, 0x22, 0xFF);
	SDL_RenderFillRect(rend, &p);
	SDL_SetRenderDrawColor(rend, 0x44, 0x44, 0x44, 0xFF);
	SDL_RenderFillRect(rend, &(SDL_Rect){p.x + 2, p.y + 2, p.w - 4, p.h - 4});
	display_fps(rend, env);
	display_render_time(env, rend);
	sprintf(s, "Samples: %u", env->scene.sampls);
	sgl_draw_str(s, &(t_font){"SourceSans", 12, 0xEEEEEE, 0},
					(t_point){5, 15, 0}, rend);
}
