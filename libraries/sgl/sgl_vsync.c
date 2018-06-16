/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_vsync.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 17:06:25 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/26 14:18:11 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sgl_private.h"

void	sgl_vsync(void)
{
	int				delay;
	static t_uint	t_b;
	static char		v_sync = 1;

	v_sync == 1 ? v_sync = SDL_GL_SetSwapInterval(1) : 0;
	if (v_sync)
	{
		delay = 17 - (SDL_GetTicks() - t_b);
		SDL_Delay(delay < 0 ? 0 : delay);
		t_b = SDL_GetTicks();
	}
}
