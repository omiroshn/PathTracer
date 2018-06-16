/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sgl_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 13:59:36 by pgritsen          #+#    #+#             */
/*   Updated: 2018/02/09 17:33:05 by pgritsen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SGL_PRIVATE_H
# define SGL_PRIVATE_H

# include "libft.h"
# include "sgl.h"
# include <math.h>
# include <errno.h>

typedef t_dlist	t_wlist;
typedef t_dlist	t_flist;

extern t_wlist	*g_win_list;
extern t_flist	*g_font_list;

TTF_Font	*sgl_add_font(t_font *font_data);

void		s_err_handler(const char *msg, const char *add,
							int err, t_uchar stop);

#endif
